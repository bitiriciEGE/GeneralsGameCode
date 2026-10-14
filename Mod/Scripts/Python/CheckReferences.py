"""Check that every name the mod INI files reference is defined somewhere.

Usage (from the Mod folder):
    python Scripts/Python/CheckReferences.py

Needs the vanilla INI files in .Reference/INIZH (see ExtractBig.py). A typo in an upgrade name
inside TriggeredBy only shows up in game once that object exists, so this catches it earlier.
"""

import glob
import os
import re
import sys

REF = ".Reference/INIZH/Data/INI"
MOD = "GameFilesEdited/Data/INI"


def definitions(kind, files):
    names = set()
    for path in files:
        with open(path, encoding="latin-1") as f:
            for line in f:
                m = re.match(r"^%s\s+(\S+)" % kind, line)
                if m:
                    names.add(m.group(1))
    return names


def main():
    if not os.path.isdir(REF):
        print(f"{REF} is missing; extract INIZH.big first (ExtractBig.py).")
        return 2

    upgrades = definitions("Upgrade", [f"{REF}/Upgrade.ini"] + glob.glob(f"{MOD}/Upgrade/*.ini"))
    buttons = definitions("CommandButton", [f"{REF}/CommandButton.ini"] + glob.glob(f"{MOD}/CommandButton/*.ini"))
    sets = definitions("CommandSet", [f"{REF}/CommandSet.ini"] + glob.glob(f"{MOD}/CommandSet/*.ini"))
    sciences = definitions("Science", [f"{REF}/Science.ini"])
    images = definitions("MappedImage", glob.glob(f"{REF}/MappedImages/**/*.ini", recursive=True))

    problems = []

    def check(name, pool, what, where):
        if name not in pool:
            problems.append(f"{where}: {what} '{name}' is not defined")

    for path in glob.glob(f"{MOD}/**/*.ini", recursive=True):
        is_command_set_file = os.sep + "CommandSet" + os.sep in os.path.normpath(path)
        # Lines copied unchanged from a vanilla file are not ours to fix (vanilla has a few quirks).
        vanilla_path = os.path.join(REF, os.path.relpath(path, MOD))
        vanilla_lines = set()
        if os.path.isfile(vanilla_path):
            with open(vanilla_path, encoding="latin-1") as f:
                vanilla_lines = {l.rstrip("\r\n") for l in f}
        with open(path, encoding="latin-1") as f:
            for number, line in enumerate(f, 1):
                if line.rstrip("\r\n") in vanilla_lines:
                    continue
                line = line.split(";")[0]
                where = f"{os.path.relpath(path, MOD)}:{number}"
                m = re.match(r"\s*(TriggeredBy|ConflictsWith|UpgradeToGrant)\s*=\s*(.+)", line)
                if m:
                    for name in m.group(2).split():
                        check(name, upgrades, "Upgrade", where)
                m = re.match(r"\s*Upgrade\s*=\s*(\S+)", line)
                if m:
                    check(m.group(1), upgrades, "Upgrade", where)
                m = re.match(r"\s*\d+\s*=\s*(\S+)", line)
                if m and is_command_set_file:
                    check(m.group(1), buttons, "CommandButton", where)
                m = re.match(r"\s*CommandSet\s*=\s*(\S+)", line)
                if m:
                    check(m.group(1), sets, "CommandSet", where)
                m = re.match(r"\s*GrantScience\s*=\s*(\S+)", line)
                if m:
                    check(m.group(1), sciences, "Science", where)
                m = re.match(r"\s*ButtonImage\s*=\s*(\S+)", line)
                if m:
                    check(m.group(1), images, "MappedImage", where)

    print(f"upgrades={len(upgrades)} buttons={len(buttons)} command sets={len(sets)} "
          f"sciences={len(sciences)} images={len(images)}")
    if problems:
        print("\n".join(problems))
        return 1
    print("All references are defined.")
    return 0


if __name__ == "__main__":
    sys.exit(main())

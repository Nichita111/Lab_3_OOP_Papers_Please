# C++ Classifier (Automated)

This implementation reads `input.json` (at the repo root) and writes the four universe groupings into `cpp-classification/resources/output/` as pretty-printed JSON.

## Build

Use any C++17 compiler. With MinGW g++ installed:

```powershell
cd "c:\Users\Nikita\Desktop\OOP\oop-course-repo\lab-papers-please"
# Build
g++ -std=c++17 "cpp-classification/src/main.cpp" -o "cpp-classification/classifier.exe"
```

## Run

```powershell
# Default: read root input.json and write to cpp-classification/resources/output
./cpp-classification/classifier.exe --input "input.json" --output "cpp-classification/resources/output"
```

You can change paths via flags:

- `--input <path>`: path to the input JSON array of individuals
- `--output <dir>`: directory where to write `star-wars.json`, `hitch-hiker.json`, `marvel.json`, `rings.json`

## Notes

- Classification logic follows `classification.md` strictly and only assigns individuals when all defining attributes are known and match (certainty). Entries that cannot be determined with certainty are not written to any universe.

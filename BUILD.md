# BUILD.md

Short build instructions for Task-scheduler-and-CPU-simulation

Prerequisites
- A C++ toolchain (g++, MinGW/MinGW-w64 on Windows, or GCC/Clang on Linux/macOS).

Windows (MinGW / g++)
1. Open a terminal (cmd, PowerShell, or Git Bash) in the repository root.
2. Run:

   g++ main.cpp src/*.cpp -I include -o scheduler.exe

3. Run the program:

   .\scheduler.exe

Linux / macOS
1. Open a terminal in the repository root.
2. Run:

   g++ main.cpp src/*.cpp -I include -o scheduler
   chmod +x scheduler

3. Run the program:

   ./scheduler

Notes & troubleshooting
- If compilation fails with header not found, check the include paths and ensure files are present in the include/ directory.
- If you prefer an IDE, configure a build task in VS Code or use a Makefile/CMake.
- The repository contains a small batch script (c.bat) that compiles and runs the program; run it with `c.bat` on Windows.

Don't commit compiled binaries
- It's recommended not to keep compiled binaries (e.g., scheduler.exe) in the repository. Instead:
  - To remove the binary from the repo but keep it locally:

    git rm --cached scheduler.exe
    echo "scheduler.exe" >> .gitignore
    git add .gitignore
    git commit -m "Remove compiled binary and add to .gitignore"
    git push

  - To permanently delete it from the repo and remote history you may need to use tools like `git filter-repo` (advanced) — ask if you need help.

Sharing builds with teammates
- For one-off sharing, upload the executable to your team chat (Telegram supports files up to 2 GB).
- For a reproducible workflow, use GitHub Releases (attach compiled artifacts) or CI (GitHub Actions) to build and publish artifacts automatically.

Recommended team workflow
- Keep source code in the repo, add BUILD.md with build steps (this file).
- Add `.gitignore` entries for built/binary files.
- Optionally add a GitHub Actions workflow to build and publish releases for your teammates.
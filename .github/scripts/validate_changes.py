#!/usr/bin/env python3
"""Reject out-of-scope edits; compile changed standalone examples; run root tests."""
from pathlib import Path
import subprocess
import tempfile

root = Path(__file__).resolve().parents[2]
status = subprocess.check_output(['git', 'status', '--porcelain=v1', '-z', '--untracked-files=all'], cwd=root)
paths = []
for entry in status.split(b'\0'):
    if not entry:
        continue
    code, name = entry[:2], entry[3:].decode('utf-8')
    if b'R' in code or b'C' in code or b'D' in code:
        raise SystemExit('Deletion/rename/copy needs human review; no automatic commit.')
    path = Path(name)
    if path.parts[0] not in {'Practice Questions', 'src', 'include', 'tests'}:
        raise SystemExit(f'Out-of-scope edit rejected: {name}')
    if path.suffix not in {'.cpp', '.cc', '.cxx', '.hpp', '.h'}:
        raise SystemExit(f'Non-code edit rejected: {name}')
    paths.append(path)
subprocess.run(['git', 'diff', '--check'], cwd=root, check=True)
with tempfile.TemporaryDirectory() as output:
    for i, path in enumerate(paths):
        if path.parts[0] == 'Practice Questions' and path.suffix in {'.cpp', '.cc', '.cxx'}:
            subprocess.run(['g++', '-std=c++17', '-Wall', '-Wextra', '-Wpedantic',
                            str(root / path), '-o', str(Path(output) / f'example-{i}')], check=True)
    build = str(Path(output) / 'build')
    subprocess.run(['cmake', '-S', str(root), '-B', build], check=True)
    subprocess.run(['cmake', '--build', build, '--parallel', '2'], check=True)
    subprocess.run(['ctest', '--test-dir', build, '--output-on-failure'], check=True)
print(f'Validated {len(paths)} changed code files and existing root tests. '
      'Compilation alone does not prove exercise behavior correct.')

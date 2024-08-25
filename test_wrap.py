from pathlib import Path
import os
import subprocess


def valid_maps(wd: Path):
    inval_path = wd.joinpath('MAPS/VALID')

    for root, _, files in os.walk(str(inval_path)):
        for file in files:
            fullname = Path(root).joinpath(file)
            yield fullname, fullname.suffix


def invalid_maps(wd: Path):
    inval_path = wd.joinpath('MAPS/NONVALID')

    for root, _, files in os.walk(str(inval_path)):
        for file in files:
            fullname = Path(root).joinpath(file)
            yield fullname, fullname.suffix


cwd = Path().cwd()
test_root = cwd.joinpath('cub_test3r')
bin = Path('cub3d')
os.chdir(test_root)

# test invalid
print("Start test for invalid maps")
for path, suffix in invalid_maps(test_root):

    if not suffix:
        print(f'---{str(path)}')
        print('Hidden file invalid maar waarom?')
        continue

    print(f'{str(path)}')
    result = subprocess.run(f'../{bin} {path}', shell=True, capture_output=True)
    assert result.returncode != 0
    assert result.stdout.decode() == ''
    assert result.stderr.decode() != ''
print("End test for invalid maps\n")

# test valid
print("Start test for valid maps")
for path, suffix in valid_maps(test_root):
    print(f'{str(path)}')
    result = subprocess.run(f'../{bin} {path}', shell=True, capture_output=True)
    assert result.returncode == 0
    assert result.stdout.decode() == ''
    assert result.stderr.decode() == ''
print("End test for valid maps")

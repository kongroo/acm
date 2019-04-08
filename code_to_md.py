import sys
import glob

with open('result.md' if len(sys.argv) < 2 else sys.argv[1], 'w') as fout:
    for f in glob.glob('**/*.cc'):
        fout.write(f'## {f}\n\n')
        fout.write('```c++\n')
        fout.write(open(f).read())
        fout.write('```\n\n')

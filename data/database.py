import sys

def main():
    if len( sys.argv ) < 2:
        print("Inform the # of entries")
        exit(1)
    preamble = 'url'
    nEntries = int( sys.argv[1] )
    with open('database.db', 'w') as fout:
        for i in range(nEntries):
            fout.write( '{}{}\n'.format(preamble, 2*i) )
    with open('insert.db', 'w') as fout:
        fout.write( '{}{}\n'.format(preamble, 1) )
    with open('remove.db', 'w') as fout:
        fout.write( '{}{}\n'.format(preamble, 1) )

if __name__ == '__main__':
    main()

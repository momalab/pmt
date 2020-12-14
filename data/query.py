import sys

def main():
    if len( sys.argv ) < 2:
        print("Inform the # of entries")
        exit(1)
    preamble = 'url'
    nEntries = int( sys.argv[1] )
    with open('queries.db', 'w') as fout:
        for i in range(nEntries):
            fout.write( '{}{}\n'.format(preamble, i) )

if __name__ == '__main__':
    main()

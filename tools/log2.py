import math
import sys

def main():
    length = len( sys.argv )
    if length < 3:
        print("Inform the number and ceil/floor")
        exit(1)
    n = int( sys.argv[1] )
    isCeil = True if sys.argv[2] == "ceil" else False
    log2 = math.log2(n)
    print( int( math.ceil(log2) if isCeil else math.floor(log2) ) )

if __name__ == '__main__':
    main()

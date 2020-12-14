import math
import sys

def m(sz, p, k, n, logp):
    m0 = math.ceil( sz * -k / math.log(1 - math.e ** (math.log(p) / k)) )
    mr = m0 % (n * logp)
    m1 = 0 if not mr else n * logp - mr
    return m0 + m1

def main():
    length = len( sys.argv )
    if length < 5:
        print("Inform the # of entries, prob, h, n, [p]")
        exit(1)
    nEntries = int( sys.argv[1] )
    prob = float( sys.argv[2] )
    h = int( sys.argv[3] )
    n = 1 << int( sys.argv[4] )
    logp = math.floor( math.log2( int( sys.argv[5] ) ) if length >= 6 else 1 )

    print( int( m(nEntries, prob, h, n, logp) ) )

if __name__ == '__main__':
    main()

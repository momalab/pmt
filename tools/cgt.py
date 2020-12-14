import sys

text = [
"""password = hello_world
SealBridge : bridge
{
    encryption = seal
    module = bridge.seal
    encoder = batch
    polyModulusDegree = ""","""
    plaintextModulus = ""","""
}
SecureMod : ring
{
    postfix = Ea
    encryption = @SealBridge
}
Secure : circuit
{
    postfix = Ep
    postneg = En
    encryption = @SealBridge
    circuitDB = tfhe # seal / seals
    sizes = ""","""
}
""" ]

def main():
    args = sys.argv[1:]
    if len(args) < 3:
        print("Inform log(n), p, and size")
        exit(1)

    with open( 'cgt.tmp'.format(args[1]), 'w' ) as fout:
        for i in range( len(args) ):
            fout.write( '{}{}'.format(text[i], args[i]) )
        fout.write( text[-1] )

if __name__ == "__main__":
    main()

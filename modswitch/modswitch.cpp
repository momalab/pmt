#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "seal/seal.h"

using namespace seal;
using namespace std;

int main(int argc, char* argv[])
{
    if ( argc < 2 )
    {
        cout << "Inform the degree of the polynomial modulus\n";
        return 1;
    }

    uint64_t n = 1 << stoull( argv[1] );
    uint64_t p = 65537; //stoull( argv[2] );

    EncryptionParameters params(scheme_type::BFV);
    params.set_poly_modulus_degree(n);
    params.set_coeff_modulus(CoeffModulus::BFVDefault(n));
    params.set_plain_modulus(p);
    auto context = SEALContext::Create(params);
    auto qualifiers = context->first_context_data()->qualifiers();
    cout << "Batching enabled: " << boolalpha << qualifiers.using_batching << endl;

    KeyGenerator keygen(context);
    PublicKey public_key = keygen.public_key();
    SecretKey secret_key = keygen.secret_key();
    RelinKeys relin_keys = keygen.relin_keys();
    Encryptor encryptor(context, public_key);
    Evaluator evaluator(context);
    Decryptor decryptor(context, secret_key);
    BatchEncoder encoder(context);

    size_t slots = encoder.slot_count();
    cout << "# slots: " << slots << "\n";

    vector<uint64_t> vi;
    for ( uint64_t i=0; i<slots; i++ ) vi.push_back(i);

    Plaintext pt;
    encoder.encode(vi, pt);

    Ciphertext ct;
    encryptor.encrypt(pt, ct);

    string preamble = "ciphertext";
    string ext = ".data";
    size_t i=0;
    auto context_data = context->first_context_data();
    while ( context_data )
    {
        cout << "Noise budget: " << decryptor.invariant_noise_budget(ct) << " bits" << endl;
        string filename = preamble + "_" + to_string(n) + "_" + to_string(p) + "_" + to_string(i++) + ext;
        ofstream fout( filename, ios::binary );
        ct.save(fout);
        context_data = context_data->next_context_data();
        if ( context_data ) evaluator.mod_switch_to_next_inplace(ct);
    }
}

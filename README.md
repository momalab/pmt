# Real-time Private Membership Test using Homomorphic Encryption

We use Bloom filters and Homomorphic Encryption (BFV) to enable Private Membership Test with a query complexy of O(1) under 0.3s in a single-thread execution, insertions and deletions with complexity O(n), and a practical setup time for databases with up to a few million entries.

This work has been accepted for publication at DATE 2021. A link will be added once it has been published.

### Install dependencies:
```
./dependencies.sh
```

### Generate database:
In directory <code>elementwise</code> or <code>groupwise</code>:
```
make prepare_database
```
It will create a database for testing purposes, and values to be queried, inserted, and removed.

### Compile and run:
In directory <code>elementwise</code> or <code>groupwise</code>:
```
make
```
### Other commands:

<ul>
<li><code>make compile</code>: compiles all programs</li>
<li><code>make query</code>: checks if the items in <code>data/query.db</code> are part of the database</li>
<li><code>make insert</code>: inserts the content of <code>data/insert.db</code> in the database</li>
<li><code>make remove</code>: removes the content of <code>data/remove.db</code> from the database</li>
</ul>

### Cite us:
E. Chielle, H. Gamil and M. Maniatakos, "Real-time Private Membership Test using Homomorphic Encryption," 2021 Design, Automation & Test in Europe Conference & Exhibition (DATE), 2021, pp. 1282-1287, doi: 10.23919/DATE51398.2021.9473968.
```
@INPROCEEDINGS{9473968,
  author={Chielle, Eduardo and Gamil, Homer and Maniatakos, Michail},
  booktitle={2021 Design, Automation   Test in Europe Conference   Exhibition (DATE)},
  title={Real-time Private Membership Test using Homomorphic Encryption},
  year={2021},
  volume={},
  number={},
  pages={1282-1287},
  doi={10.23919/DATE51398.2021.9473968}
}
```

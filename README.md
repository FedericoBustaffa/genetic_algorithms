# Algoritmi genetici

## Compilazione e utilizzo

Per prima cosa clonare la libreria

```bash
git clone --recurse-submodules https://github.com/FedericoBustaffa/genetic_algorithms.git
```

Una volta clonata installare i pacchetti necessari con `pip` tramite il comando

```bash
cd genetic_algorithms
pip install -r requirements.txt
```

Compilare il modulo con `cmake`

```bash
mkdir build
cd build
cmake ..
make
```

Una volta compilata la libreria sarà possibile
installarla con `pip` spostandosi nella directory con
lo script `setup.py` ed eseguendo il comand

```bash
pip install .
```

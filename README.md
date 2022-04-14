# energy-kernel2
Study of Energy Simulation Kernel (with and without approximations)

 * Gabriel García Castañé    - gabriel.gonzalezcastane AT ucc.ie
 * Rafael Tolosana Calasanz  - rafaelt AT unizar.es
 * Alejandro Calderón Mateos - acaldero AT inf.uc3m.es


## Get started

1) First you need to install the pre-requisites:
```bash
  apt-get -y install build-essential
  apt-get -y install gnuplot gnuplot-data gnuplot-doc inkscape
```

2) Then, clone the proyect:
```bash
  git clone https://github.com/acaldero/energy-kernel2
```

3) Finally, run the benchmarks:
```bash
  mkdir -p results
  ./do_clean.sh
  ./do_compile.sh
  ./do_execute.sh
  ./do_plot.sh
  ls *.pdf
```

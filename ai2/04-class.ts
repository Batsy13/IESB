interface Individual {
  genes: number[];
}

function cross(binpop: Individual[], selected: Individual[]): Individual[] {
  const nInd = selected.length;
  const lInd = binpop[0].genes.length;
  const newPopulation: Individual[] = new Array(nInd);

  for (let i = 0; i < nInd / 2; i++) {
    const parentAIndex = Math.floor(Math.random() * nInd);
    const parentBIndex = Math.floor(Math.random() * nInd);
    const cp = Math.floor(Math.random() * (lInd - 1)) + 1;

    const parentA = selected[parentAIndex].genes;
    const parentB = selected[parentBIndex].genes;

    const childOneGenes = [
      ...parentA.slice(0, cp),
      ...parentB.slice(cp)
    ];

    const childTwoGenes = [
      ...parentB.slice(0, cp),
      ...parentA.slice(cp)
    ];

    newPopulation[i] = { genes: childOneGenes };
    newPopulation[i + nInd / 2] = { genes: childTwoGenes };
  }

  return newPopulation;
}

function mutate(binpop: Individual[], pmut: number): Individual[] {
  const nInd = binpop.length;
  const lInd = binpop[0].genes.length;

  for (let i = 0; i < nInd; i++) {
    if (Math.random() < pmut) {
      
      const mp = Math.floor(Math.random() * lInd);

      binpop[i].genes[mp] = binpop[i].genes[mp] === 0 ? 1 : 0;
    }
  }

  return binpop;
}

const initialPopulation: Individual[] = [
  { genes: [1, 1, 0, 0, 0] },
  { genes: [0, 0, 1, 1, 1] },
  { genes: [1, 0, 1, 0, 1] },
  { genes: [0, 1, 0, 1, 0] }
];

console.log("--- Initial Population ---");
console.table(initialPopulation.map(ind => ind.genes));

const crossedPopulation = cross(initialPopulation, initialPopulation);

console.log("\n--- After Crossover ---");
console.table(crossedPopulation.map(ind => ind.genes));

const mutatedPopulation = mutate(crossedPopulation, 0.5);

console.log("\n--- After Mutation (50% rate) ---");
console.table(mutatedPopulation.map(ind => ind.genes));
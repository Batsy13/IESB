function generatePopulation(populationSize: number, boundaries: number[][]) {
  let population = [];

  for (let i = 0; i < populationSize; i++) {
    let individual = [];
    for (let j = 0; j < boundaries.length; j++) {
      let min = boundaries[j][0];
      let max = boundaries[j][1];
      let gene = Math.random() * (max - min) + min;
      individual.push(gene);
    }
    population.push(individual);
  }

  return population;
}

let populationSize = 5;
let geneBoundaries = [
  [0, 10],
  [5, 15],
  [-1, 1],
];

console.log(generatePopulation(populationSize, geneBoundaries));
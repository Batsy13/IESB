const population: number[][] = [
  [1.0, 0.5],
  [2.0, 2.0],
  [0.1, 0.2],
  [3.0, 1.5]
];

function calculateFitness(population: number[][]): number[] {

    let nInd = population.length;
    const fitness: number[] = new Array(nInd)

    for(let i = 0; i < nInd; i++) {
        fitness[i] = objectiveFunction(population[i])
    }

    return fitness

}

function objectiveFunction(x: number[]): number {

    const nChrom = x.length;
    let result = 10

    for (let j = 0; j < nChrom; j++){
        result = result - (x[j] * x[j])
    }

    return result
}

function rouletteWheelSelection(population: number[][], fitnessScores: number[]): number[] {
    const totalFitness = fitnessScores.reduce((sum, score) => sum + score, 0);
  const nInd = population.length;
  
  const randomPoint = Math.random() * totalFitness;
  
  let cumulativeSum = 0;
  for (let i = 0; i < nInd; i++) {
      cumulativeSum += fitnessScores[i];
      if (cumulativeSum >= randomPoint) {
      return population[i];
    }
}

return population[nInd - 1];
}

const scores = calculateFitness(population);
const selectedIndividual = rouletteWheelSelection(population, scores);

console.log("Fitness Scores:", scores);
console.log("Selected Individual:", selectedIndividual);
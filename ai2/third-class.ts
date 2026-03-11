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

let population = [
    [5, 10, 0],
    [2, 7, -0.5]
];

console.log(calculateFitness(population))

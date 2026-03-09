function binaryCod(population: number[][], boundaries: number[][], bits: number[]) {
    let code = [];
    
    for (let i = 0; i < population.length; i++) {
        let temp = "";
        for (let j = 0; j < boundaries.length; j++) {
            let inf = boundaries[j][0];
            let sup = boundaries[j][1];
            
            let val = ((population[i][j] - inf) / (sup - inf)) * (Math.pow(2, bits[j]) - 1);
            let aux = Math.round(val).toString(2).padStart(bits[j], '0');
            
            if (j === 0) {
                temp = aux;
            } else {
                temp = temp + aux;
            }
        }
        code[i] = temp;
    }
    return code;
}

let population = [
    [5, 10, 0],
    [2, 7, -0.5]
];
let geneBoundaries = [
    [0, 10],
    [5, 15],
    [-1, 1],
];
let bits = [8, 8, 8];

console.log(binaryCod(population, geneBoundaries, bits));
function decode(binpop: string[], boundaries: number[][], bits: number[]) {
    let nInd = binpop.length;
    let nCrom = boundaries.length;
    let decodedPop = Array.from({ length: nInd }, () => new Array(nCrom));

    for (let i = 0; i < nInd; i++) {
        let currentPos = 0;
        for (let j = 0; j < nCrom; j++) {
            let inf = boundaries[j][0];
            let sup = boundaries[j][1];
            let numBits = bits[j];

            let bitString = binpop[i].substring(currentPos, currentPos + numBits);
            let decimalVal = parseInt(bitString, 2);

            let realVal = inf + (decimalVal * (sup - inf)) / (Math.pow(2, numBits) - 1);
            
            decodedPop[i][j] = realVal;
            currentPos += numBits;
        }
    }
    return decodedPop;
}

let binaryPopulation = ['100000001000000010000000', '001100110011001101000000'];
let geneBoundaries = [
    [0, 10],
    [5, 15],
    [-1, 1],
];
let bitsPerGene = [8, 8, 8];

console.table(decode(binaryPopulation, geneBoundaries, bitsPerGene));
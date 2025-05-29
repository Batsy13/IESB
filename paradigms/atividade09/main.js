const { Worker, isMainThread, parentPort, workerData } = require('worker_threads');

function isPrime(num) {
  if (num <= 1) return false;
  if (num <= 3) return true;
  if (num % 2 === 0 || num % 3 === 0) return false;
  for (let i = 5; i * i <= num; i = i + 6) {
    if (num % i === 0 || num % (i + 2) === 0) return false;
  }
  return true;
}

if (isMainThread) {
  const maxNumber = 99999;
  const range = 10000;
  const numThreads = Math.ceil(maxNumber / range);

  for (let i = 0; i < numThreads; i++) {
    const start = i * range + 1;
    const end = Math.min((i + 1) * range, maxNumber);

    const worker = new Worker(__filename, {
      workerData: { start, end, threadId: i },
    });

    worker.on('message', (prime) => {
      console.log(`${i}: ${prime}`);
    });

    worker.on('error', (err) => {
      console.error(`Erro no worker ${i}:`, err);
    });

    worker.on('exit', (code) => {
      if (code !== 0) {
        console.error(`Worker ${i} parou com código ${code}`);
      }
    });
  }
} else {
  const { start, end, threadId } = workerData;

  for (let num = start; num <= end; num++) {
    if (isPrime(num)) {
      parentPort.postMessage(num);
    }
  }
}
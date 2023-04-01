export function RSI(closingPrices: any[]) {
  let avgUpwardChange = 0;
  for (let i = 1; i < closingPrices.length; i++)
    avgUpwardChange += Math.max(0, closingPrices[i] - closingPrices[i - 1]);
  avgUpwardChange /= closingPrices.length;

  let avgDownwardChange = 0;
  for (let i = 1; i < closingPrices.length; i++)
    avgDownwardChange += Math.max(0, closingPrices[i - 1] - closingPrices[i]);
  avgDownwardChange /= closingPrices.length;

  const rsi = 100 - (100 / (1 + (avgUpwardChange / avgDownwardChange)));

  return rsi;
}

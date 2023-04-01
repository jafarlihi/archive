import { tokens } from './tokens.js';

export let balance: { symbol: string, amount: number }[] = [];

export const addBalance = (symbol: string, amount: number) => {
  if (balance.find((b) => b.symbol === symbol)) {
    balance.find((b) => b.symbol === symbol)!.amount += amount;
  } else {
    balance.push({ symbol, amount });
  }
};

export const removeBalance = (symbol: string) => {
  balance = balance.filter((b) => b.symbol !== symbol);
};

export const balanceUSDValue = (timeIndex: number) => {
  let usd = 0;
  for (const b of balance) {
    const token = tokens.find((t) => t.symbol === b.symbol);
    if (Number.isNaN(token!.closingPrices[timeIndex]))
      console.log('[WARNING] closingPrices[timeIndex] NaN found!!!');
    if (Number.isNaN(b.amount))
      console.log('[WARNING] b.amount NaN found!!!');
    usd += token!.closingPrices[timeIndex] * b.amount;
  };
  return usd;
}

export const purgeBalance = () => {
  balance = [];
};

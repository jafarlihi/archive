import { addBalance, balance, removeBalance } from './balance.js';
import { Strategy } from './strategy.js';
import { Token } from './tokens.js';

export const trade = (strat: Strategy, timeIndex: number) => {
  const swappable = strat.exec(timeIndex);
  for (let i = 0; i < swappable.length; i += 2) {
    swap(swappable[i], swappable[i + 1], timeIndex);
    console.log(`Swapped ${swappable[i].symbol} to ${swappable[i + 1].symbol}`);
  }
};

const feeInUSD = 0;
const feeInPercent = .02;

const swap = (from: Token, to: Token, timeIndex: number) => {
  const fromBalance = balance.find((b) => b.symbol === from.symbol);
  //let fromUSDValue = from.lowPrices[timeIndex] * fromBalance!.amount - feeInUSD;
  //fromUSDValue = fromUSDValue - (fromUSDValue * feeInPercent);
  //const toAmount = fromUSDValue / to.highPrices[timeIndex];
  let fromUSDValue = from.closingPrices[timeIndex] * fromBalance!.amount - feeInUSD;
  //fromUSDValue = fromUSDValue - (fromUSDValue * feeInPercent);
  const toAmount = fromUSDValue / to.closingPrices[timeIndex];
  if (Number.isNaN(toAmount))
    console.log('[WARNING] toAmount NaN found!!!');
  removeBalance(from.symbol);
  addBalance(to.symbol, toAmount);
};

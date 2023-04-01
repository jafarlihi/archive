import { Token, tokens } from './tokens.js';
import { balance } from './balance.js';
import { RSI } from './analysis.js';
import { SuperTrend, AO, ADX, BollingerBands, DC } from '@debut/indicators';
import { ma, dma, ema, sma, wma } from 'moving-averages';

export abstract class Strategy {
  public abstract exec(timeIndex: number): Token[];
};

function shuffleArray(array: any[]) {
  for (let i = array.length - 1; i > 0; i--) {
    const j = Math.floor(Math.random() * (i + 1));
    [array[i], array[j]] = [array[j], array[i]];
  }
}

function percentage(partialValue: number, totalValue: number) {
  return (100 * partialValue) / totalValue;
}

export let totalwin = 0;
export let totalloss = 0;

export class PlsWork2 extends Strategy {
  speriod = 50;
  fperiod = 40;
  skip = 10;
  losingThreshold = 99.7;

  constructor(skip: number, speriod: number, fperiod: number, losingThreshold: number) {
    super();
    this.skip = skip;
    this.speriod = speriod;
    this.fperiod = fperiod;
    this.losingThreshold = losingThreshold;
  }

  public exec(timeIndex: number): Token[] {
    const result: Token[] = [];
    if (timeIndex % this.skip !== 0) return result;
    if (timeIndex < this.speriod + 1) return result;
    const t = tokens.find((t) => t.symbol === 'GRT')!;
    const t2 = tokens.find((t) => t.symbol === 'ETH')!;
    if (t2.closingPrices[timeIndex - this.speriod] - t2.closingPrices[timeIndex] < -50 && t2.closingPrices[timeIndex - this.speriod * 2] - t2.closingPrices[timeIndex - this.speriod] < 0 && t2.closingPrices[timeIndex - this.speriod * 3] - t2.closingPrices[timeIndex - this.speriod * 2] < 0)
      totalwin++;
    else if (t2.closingPrices[timeIndex - this.speriod] - t2.closingPrices[timeIndex] > 50 && t2.closingPrices[timeIndex - this.speriod * 2] - t2.closingPrices[timeIndex - this.speriod] > 0 && t2.closingPrices[timeIndex - this.speriod * 3] - t2.closingPrices[timeIndex - this.speriod * 2] > 0)
      totalloss++;
    return result;
  }
}


export class PlsWork extends Strategy {
  public exec(timeIndex: number): Token[] {
    const result: Token[] = [];
    if (timeIndex === 0) {
      totalwin = 0;
      totalloss = 0;
    }
    if (timeIndex < 301) return result;

    const winning: Token[] = [];
    const losing: Token[] = [];

    const t = tokens.find((t) => t.symbol === 'ETH')!;
    const st = new SuperTrend(250, 15, 'RMA');
    let value: any;
    for (let i = timeIndex - 300; i < timeIndex; i++) {
      value = st.nextValue(t.highPrices[i], t.lowPrices[i], t.closingPrices[i]);
    }
    if (value) {
      if (value.direction > 0 && percentage(t.closingPrices[timeIndex], value.superTrend) > 99) {
        totalwin++;
      } else {
        totalloss++;
      }
    }

    return result;
  }
}

export class Dumbo extends Strategy {
  public exec(timeIndex: number): Token[] {
    if (timeIndex % 50 !== 0) return [];
    if (timeIndex < 101) return [];
    const winning: any[] = [];
    const losing: any[] = [];
    for (const t of tokens) {
      const w = t.closingPrices[timeIndex - 100] - t.closingPrices[timeIndex] > 0;
      if (w) {
        const diff = percentage(t.closingPrices[timeIndex - 50], t.closingPrices[timeIndex]);
        winning.push({ t, diff });
      }
      else losing.push(t);
    }
    winning.sort((a, b) => b.diff - a.diff);
    shuffleArray(winning);
    const result: Token[] = [];
    for (const b of balance) {
      if (losing.find((l) => l.symbol === b.symbol) && winning.length > 0) {
        result.push(tokens.find((t) => t.symbol === b.symbol)!);
        result.push(winning.pop().t);
      }
    }
    return result;
  }
}

export class MACross extends Strategy {
  speriod = 50;
  fperiod = 40;
  skip = 10;
  losingThreshold = 99.7;

  constructor(skip: number, speriod: number, fperiod: number, losingThreshold: number) {
    super();
    this.skip = skip;
    this.speriod = speriod;
    this.fperiod = fperiod;
    this.losingThreshold = losingThreshold;
  }

  public exec(timeIndex: number): Token[] {
    const result: Token[] = [];
    if (timeIndex % this.skip !== 0) return result;
    if (timeIndex < this.speriod + 1) return result;
    let winning: { t: Token, v: number }[] = [];
    let losing: { t: Token, v: number }[] = [];
    for (const t of tokens) {
      if (t.symbol !== 'ETH') continue;
      const ef = wma(t.closingPrices.slice(timeIndex - this.speriod - 1, timeIndex), this.fperiod);
      const es = wma(t.closingPrices.slice(timeIndex - this.speriod - 1, timeIndex), this.speriod);
      if (ef.at(-1) > es.at(-1) && ef.at(-2) > es.at(-2)) {
        winning.push({ t, v: percentage(es.at(-1), ef.at(-1)) });
      } else if (ef.at(-1) < es.at(-1) && ef.at(-2) < es.at(-2)) { // && percentage(ef, es) < this.losingThreshold) {
        losing.push({ t, v: percentage(ef.at(-1), es.at(-1)) });
      }
    }
    totalwin += winning.length;
    totalloss += losing.length;
    if (totalwin > totalloss && balance.find((b) => b.symbol === 'USD')) {
      result.push(tokens.find((t) => t.symbol === 'USD')!);
      result.push(tokens.find((t) => t.symbol === 'LINK')!);
    }
    if (totalloss > totalwin && balance.find((b) => b.symbol === 'LINK')) {
      result.push(tokens.find((t) => t.symbol === 'LINK')!);
      result.push(tokens.find((t) => t.symbol === 'USD')!);
    }
    /*
    winning.sort((a, b) => a.v - b.v);
    shuffleArray(balance);
    for (const b of balance) {
      if (losing.find((l) => l.t.symbol === b.symbol) && winning.length > 0) {
        result.push(tokens.find((t) => t.symbol === b.symbol)!);
        result.push(winning.shift()!.t);
      }
    }
    */
    return result;
  }
}

export class SimpleBS extends Strategy {
  public exec(timeIndex: number): Token[] {
    const result: Token[] = [];
    if (timeIndex % 35 !== 0) return result;
    let losing: Token[] = [];
    let winning: Token[] = [];
    for (const t of tokens) {
      const st = new SuperTrend(80, 40, 'LWMA');
      let value: any;
      for (let i = timeIndex - 201; i < timeIndex; i++)
      value = st.nextValue(t.highPrices[i], t.lowPrices[i], t.closingPrices[i]);
      if (!value) continue;
      if (value.direction > 0) {
        if (!balance.find((b) => b.symbol === t.symbol))
          winning.push(t);
      } else
        losing.push(t);
    }
    if (losing.length > winning.length + 5) {
      if (balance[0].symbol !== 'USD') {
        result.push(tokens.find((t) => t.symbol === balance[0].symbol)!);
        result.push(tokens.find((t) => t.symbol === 'USD')!);
      }
      else if (balance.length > 1) {
        result.push(tokens.find((t) => t.symbol === balance[1].symbol)!);
        result.push(tokens.find((t) => t.symbol === 'USD')!);
      }
    }
    return result;
  }
}


export class SupertrendStrategy extends Strategy {
  public exec(timeIndex: number): Token[] {
    const result: Token[] = [];
    if (timeIndex % 35 !== 0) return result;
    let losing: Token[] = [];
    let winning: Token[] = [];
    for (const t of tokens) {
      const st = new SuperTrend(80, 40, 'LWMA');
      let value: any;
      for (let i = timeIndex - 201; i < timeIndex; i++)
      value = st.nextValue(t.highPrices[i], t.lowPrices[i], t.closingPrices[i]);
      if (!value) continue;
      if (value.direction > 0) {
        if (!balance.find((b) => b.symbol === t.symbol))
          winning.push(t);
      } else
        losing.push(t);
    }
    const winningRanking: { token: Token, rsi: number }[] = [];
    for (const t of winning) {
      const rsi = RSI(t.closingPrices.slice(timeIndex - 20, timeIndex));
      winningRanking.push({ token: t, rsi });
    }
    winningRanking.sort((a, b) => b.rsi - a.rsi);
    winning = winningRanking.map((w) => w.token);
    //if (winning.length > tokens.length - 2)
    //console.log('ALL WINNING!!!');
    if (losing.length > 0 && winning.length === 0) {
      winning.push(tokens.find((t) => t.symbol === 'USD')!);
    } else if (winning.length > 0 && !balance.some((b) => losing.find((l) => l.symbol === b.symbol))) {
      losing.push(tokens.find((t) => t.symbol === 'USD')!);
    }
    let bWinningCount = 0;
    for (const b of balance) {
      if (winning.find((w) => w.symbol === b.symbol)) {
        bWinningCount++;
        continue;
      }
      const token = tokens.find((t) => t.symbol === b.symbol);
      if (losing.find((l) => l.symbol === b.symbol) && winning.length > 0) {
        result.push(token!);
        result.push(winning.pop()!);
      } else if (losing.find((l) => l.symbol === b.symbol) && winning.length === 0) {
        //console.log('Got LOSING but no WINNING');
      }
    }
    if (bWinningCount === balance.length) {
      //console.log('Balance all WINNING');
    }
    return result;
  }
}

export class MACDStrategy extends Strategy {
  public exec(timeIndex: number): Token[] {
    return [];
  }
}

export class RSIStrategy extends Strategy {
  period = 10;
  skip = 0;
  threshold = 50;

  constructor(period: number, skip: number, threshold: number) {
    super();
    this.period = period;
    this.skip = skip;
    this.threshold = threshold;
  }

  public exec(timeIndex: number): Token[] {
    const result: Token[] = [];
    if (timeIndex < this.period || timeIndex % this.skip !== 0) return result;

    const balanceRSIRankingReverse: { symbol: string, rsi: number }[] = [];
    for (const b of balance) {
      const token = tokens.find((t) => t.symbol === b.symbol);
      const rsi = RSI(token!.closingPrices.slice(timeIndex - this.period, timeIndex));
      balanceRSIRankingReverse.push({ symbol: b.symbol, rsi });
    }
    balanceRSIRankingReverse.sort((a, b) => a.rsi - b.rsi);

    const tokenRSIRanking: typeof balanceRSIRankingReverse = [];
    for (const t of tokens) {
      const rsi = RSI(t.closingPrices.slice(timeIndex - this.period, timeIndex));
      tokenRSIRanking.push({ symbol: t.symbol, rsi });
    }
    tokenRSIRanking.sort((a, b) => b.rsi - a.rsi);

    let tokenRSIRankingIndex = 0;
    outer: for (const b of balanceRSIRankingReverse) {
      const bToken = tokens.find((t) => t.symbol === b.symbol);
      while (tokenRSIRankingIndex < tokenRSIRanking.length) {
        if (tokenRSIRanking[tokenRSIRankingIndex].rsi - b.rsi > this.threshold) {
          const tToken = tokens.find((t) => t.symbol === tokenRSIRanking[tokenRSIRankingIndex].symbol);
          if (balance.find((b) => b.symbol === tToken!.symbol)) {
            tokenRSIRankingIndex++;
            continue;
          }
          result.push(bToken!, tToken!);
          tokenRSIRankingIndex++;
          continue outer;
        } else {
          break outer;
        }
      }
    }

    return result;
  }
};

export class RSIStrategy2 extends Strategy {
  period = 10;
  skip = 0;
  threshold = 50;

  constructor(period: number, skip: number, threshold: number) {
    super();
    this.period = period;
    this.skip = skip;
    this.threshold = threshold;
  }

  public exec(timeIndex: number): Token[] {
    const result: Token[] = [];
    if (timeIndex < this.period || timeIndex % this.skip !== 0) return result;

    const balanceRSIRanking: { symbol: string, rsi: number }[] = [];
    for (const b of balance) {
      const token = tokens.find((t) => t.symbol === b.symbol);
      const rsi = RSI(token!.closingPrices.slice(timeIndex - this.period, timeIndex));
      balanceRSIRanking.push({ symbol: b.symbol, rsi });
    }
    balanceRSIRanking.sort((a, b) => a.rsi - b.rsi);

    const tokenRSIRankingReverse: typeof balanceRSIRanking= [];
    for (const t of tokens) {
      const rsi = RSI(t.closingPrices.slice(timeIndex - this.period, timeIndex));
      tokenRSIRankingReverse.push({ symbol: t.symbol, rsi });
    }
    tokenRSIRankingReverse.sort((a, b) => a.rsi - b.rsi);

    let tokenRSIRankingIndex = 0;
    outer: for (const b of balanceRSIRanking) {
      const bToken = tokens.find((t) => t.symbol === b.symbol);
      while (tokenRSIRankingIndex < tokenRSIRankingReverse.length) {
        if (b.rsi - tokenRSIRankingReverse[tokenRSIRankingIndex].rsi > this.threshold) {
          const tToken = tokens.find((t) => t.symbol === tokenRSIRankingReverse[tokenRSIRankingIndex].symbol);
          if (balance.find((b) => b.symbol === tToken!.symbol)) {
            tokenRSIRankingIndex++;
            continue;
          }
          result.push(bToken!, tToken!);
          tokenRSIRankingIndex++;
          continue outer;
        } else {
          break outer;
        }
      }
    }

    return result;
  }
};

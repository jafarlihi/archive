import { parse } from 'csv/sync';
import { promises as fs } from 'fs';

export interface Token {
  symbol: string;
  closingPrices: number[];
  highPrices: number[];
  lowPrices: number[];
};

export let tokens: Token[] = [];

export const initTokens = async (dir: string) => {
  tokens = [];
  const csvs = await fs.readdir(`/home/user2/shared/${dir}/`);
  let closingPricesLength = -1;

  for (const csv of csvs) {
    const content = await fs.readFile(`/home/user2/shared/${dir}/${csv}`);
    const records = parse(content);
    const closingPrices = records.map((r: any) => Number(r[4]));
    const highPrices = records.map((r: any) => Number(r[2]));
    const lowPrices = records.map((r: any) => Number(r[3]));
    if (closingPricesLength === -1)
      closingPricesLength = closingPrices.length;
    if (closingPricesLength !== closingPrices.length) {
      console.log('[WARNING] closingPricesLength difference found!!!');
      continue;
      //normalizeClosingPrices(tokens.at(-1)?.closingPrices!, closingPrices);
    }
    if (closingPrices.some((p: number) => Number.isNaN(p)))
      console.log('[WARNING] closingPrice NaN found!!!')
    let symbolEnd = csv.indexOf('USDT');
    if (symbolEnd === -1)
      symbolEnd = csv.indexOf('BUSD');
    tokens.push({ symbol: csv.slice(0, symbolEnd), closingPrices, highPrices, lowPrices });
  }

  tokens.push({ symbol: 'USD', closingPrices: Array(tokens[0].closingPrices.length).fill(1), highPrices: Array(tokens[0].highPrices.length).fill(1), lowPrices: Array(tokens[0].lowPrices.length).fill(1) });
};

const normalizeClosingPrices = (correct: number[], incorrect: number[]) => {
  console.log(`Length difference: ${correct.length - incorrect.length}`);
};

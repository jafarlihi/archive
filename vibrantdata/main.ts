import { initTokens, tokens } from './tokens.js';
import { addBalance, balanceUSDValue } from './balance.js';
import { trade } from './trade.js';
import { totalwin, totalloss, PlsWork2, PlsWork, Dumbo, MACross, SimpleBS, RSIStrategy, RSIStrategy2, SupertrendStrategy } from './strategy.js';

const process = async (dir: string) => {
  await initTokens(dir);

  let timeIndex = 0;
  const starting = balanceUSDValue(timeIndex);
  console.log(`Starting balance: ${balanceUSDValue(timeIndex)}`);
  while (timeIndex < tokens[0].closingPrices.length - 1) {
    trade(new RSIStrategy2(100, 50, 15), timeIndex);
    //trade(new SupertrendStrategy(), timeIndex);
    //trade(new SimpleBS(), timeIndex);
    //trade(new MACross(100, 300, 200, 99), timeIndex);
    //trade(new RSIStrategy(50, 10, 80), timeIndex);
    //trade(new Dumbo(), timeIndex);
    //trade(new PlsWork(), timeIndex);
    //trade(new PlsWork2(200, 2500, 10, 100), timeIndex);
    timeIndex++;
  }
  console.log(`Ending balance: ${balanceUSDValue(timeIndex)}`);
  const ending = balanceUSDValue(timeIndex);
  /*
  if (starting > ending) {
    if (totalwin < totalloss) console.log('correct');
    else console.log('incorrect');
  } else {
    if (totalwin > totalloss) console.log('correct');
    else console.log('incorrect');
  }
  */
  //console.log(totalwin);
  //console.log(totalloss);
};

addBalance('LINK', 100);


await process('5m-2022-01');
await process('5m-2022-02');
await process('5m-2022-03');
await process('5m-2022-04');
await process('5m-2022-05');
await process('5m-2022-06');
await process('5m-2022-07');
await process('5m-2022-08');
await process('5m-2022-09');
await process('5m-2022-10');
await process('5m-2022-11');
await process('5m-2022-12');
await process('5m-2023-01');


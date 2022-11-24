import * as fs from 'fs';
import * as dotenv from 'dotenv';
import Big from 'big.js';

dotenv.config();

function calculate(value) {
  return value.times(2).plus(1.5).div(7.5);
}

function normalizeFraction(value) {
  if (value.length > 20)
    return value.substring(0, 20);
  else if (value.length < 20) {
    return value.padEnd(20, '0');
  }
}

function run() {
  dotenv.config({ override: true });
  const value = new Big(process.env.VALUE);
  const updatedValue = normalizeFraction(calculate(value).toString());
  fs.writeFileSync('./.env', 'VALUE=' + updatedValue);
  fs.appendFileSync('./history.csv', updatedValue + ',' + new Date().toISOString() + '\n');
}

function main() {
  run();
  setInterval(run, 60 * 1000 * 2);
}
main();

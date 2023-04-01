import { BigNumber } from '@ethersproject/bignumber'
import { type Token, tokens } from './tokens.js'
import { addBalance, balance, removeBalance } from './balance.js'
import { appendLog } from './log.js'
import { DEBUG } from './main.js'

export const trade = () => {
  const candidates: Array<{ t: Token, diff: BigNumber[] }> = []
  for (const t of tokens) {
      if ((t.performance() != null) && t.performance()![0].gt(BigNumber.from('0'))) // TODO: Telescope this from 4 checks to 3 checks and so on
    {
      candidates.push({ t, diff: t.performance()! })
      if (DEBUG) appendLog(`New candidate: ${candidates.at(-1)}`);
    }
  }
  candidates.sort((a, b) => b.diff[1].sub(a.diff[1]).toNumber())

  const toDelete: Array<{ symbol: string, amount: BigNumber }> = []

  outer: for (const b of balance) {
    const token = tokens.find((t) => t.symbol === b.symbol)
    if (((token?.performance()) != null) && token?.performance()![0].lt(BigNumber.from('0'))) {
      if (DEBUG && candidates.length === 0) { appendLog(`Have ${b.symbol} to swap but no candidates!`) }
      for (const candidate of candidates) {
        if (balance.find((b) => b.symbol === candidate.t.symbol) == null) {
          swap(b, candidate.t)
          toDelete.push(b)
          continue outer
        }
      }
    }
  }

  for (const d of toDelete) { removeBalance(d.symbol) }
}

const swap = (from: { symbol: string, amount: BigNumber }, to: Token) => {
  const fromToken = tokens.find((t) => t.symbol === from.symbol) // TODO: Store Token in balance entries
  const fiveUsdWei = BigNumber.from('590000000000000')
  const wei = from.amount.mul(fromToken!.prices.at(-1)!)
  const buyWei = wei.sub(fiveUsdWei)
  const amount = buyWei.div(to.prices.at(-1)!)
  addBalance(to.symbol, amount)
  appendLog(`Swapped ${from.symbol} for ${to.symbol}`)
}

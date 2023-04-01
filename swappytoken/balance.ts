import { BigNumber } from '@ethersproject/bignumber'
import { ethers } from 'ethers'
import { tokens } from './tokens.js'

export let balance: Array<{ symbol: string, amount: BigNumber }> = []

export function currentBalance (): string {
  let result = BigNumber.from('0')
  for (const b of balance) {
    const price = tokens.find((t) => t.symbol === b.symbol)?.prices.at(-1)
    if (price != null) { result = result.add(price.mul(b.amount)) }
  }
  return ethers.formatEther(result.toBigInt()).toString()
}

export function removeBalance (symbol: string) {
  balance = balance.filter((b) => {
    return b.symbol !== symbol
  })
}

export function addBalance (symbol: string, amount: BigNumber) {
  balance.push({ symbol, amount })
}

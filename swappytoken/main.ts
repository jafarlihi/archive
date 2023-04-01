import blessed from 'blessed'
import { BigNumber } from '@ethersproject/bignumber'
import { fetchTokenPrices } from './api.js'
import { tokensToString } from './tokens.js'
import { addBalance, currentBalance } from './balance.js'
import { trade } from './trade.js'
import { log, clearLog } from './log.js'

export const DEBUG = false

const screen = blessed.screen({
  smartCSR: true
})

screen.title = 'swappytoken'

const tokenBox = blessed.box({
  width: '50%',
  height: '90%',
  tags: true,
  border: {
    type: 'line'
  },
  style: {
    fg: 'white',
    bg: 'black',
    border: {
      fg: '#f0f0f0'
    }
  },
  scrollable: true,
  alwaysScroll: true
})
const balanceBox = blessed.box({
  top: '90%',
  width: '50%',
  height: '10%',
  tags: true,
  border: {
    type: 'line'
  },
  style: {
    fg: 'white',
    bg: 'black',
    border: {
      fg: '#f0f0f0'
    }
  }
})
const logBox = blessed.box({
  left: '50%',
  width: '50%',
  height: '100%',
  tags: true,
  border: {
    type: 'line'
  },
  style: {
    fg: 'white',
    bg: 'black',
    border: {
      fg: '#f0f0f0'
    }
  },
  scrollable: true,
  alwaysScroll: true
})

screen.append(tokenBox)
screen.append(balanceBox)
screen.append(logBox)

screen.key(['escape', 'q', 'C-c'], function (ch, key) {
  return process.exit(0)
})

screen.key(['t'], function (ch, key) {
  trade()
})

screen.key(['s'], function (ch, key) {
  tokenBox.scroll(1)
  logBox.scroll(1)
})

screen.key(['w'], function (ch, key) {
  tokenBox.scroll(-1)
  logBox.scroll(-1)
})

screen.key(['c'], function (ch, key) {
  clearLog()
})

tokenBox.focus()

const updateTokensThread = async () => {
  while (true) {
    await fetchTokenPrices()
    await new Promise(r => setTimeout(r, 10000))
  }
}

const tokenBoxThread = async () => {
  while (true) {
    tokenBox.setContent(tokensToString())
    screen.render()
    await new Promise(r => setTimeout(r, 500))
  }
}

const balanceBoxThread = async () => {
  while (true) {
    balanceBox.setContent(currentBalance())
    screen.render()
    await new Promise(r => setTimeout(r, 500))
  }
}

const logBoxThread = async () => {
  while (true) {
    logBox.setContent(log)
    screen.render()
    await new Promise(r => setTimeout(r, 500))
  }
}

const tradeThread = async () => {
  while (true) {
    await new Promise(r => setTimeout(r, 20000))
    trade()
  }
}

addBalance('LINK', BigNumber.from('150'))
addBalance('1INCH', BigNumber.from('500'))
addBalance('BNB', BigNumber.from('2'))
addBalance('BAT', BigNumber.from('500'))
addBalance('AMP', BigNumber.from('10000'))

tokenBoxThread()
balanceBoxThread()
logBoxThread()
updateTokensThread()
tradeThread()
screen.render()

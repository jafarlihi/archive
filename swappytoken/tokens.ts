import { BigNumber } from '@ethersproject/bignumber'
import { DEBUG } from './main.js'

const percentageChange = (a: BigNumber, b: BigNumber) => b.sub(a).div(a).mul(BigNumber.from('100'))

export class Token {
  address: string
  decimals: number
  symbol: string
  name: string
  prices: BigNumber[]

  constructor (address: string, decimals: number, symbol: string, name: string) {
    this.address = address
    this.decimals = decimals
    this.symbol = symbol
    this.name = name
    this.prices = []
  }

  public addPrice (price: BigNumber): void {
    this.prices.push(price)
  }

  // TODO: Broken
  public tokenPerformanceLast4 (): number[] | undefined {
    if (this.prices.length < 5) { return undefined }
    return [
      percentageChange(this.prices.at(-5)!, this.prices.at(-4)!).toNumber(),
      percentageChange(this.prices.at(-4)!, this.prices.at(-3)!).toNumber(),
      percentageChange(this.prices.at(-3)!, this.prices.at(-2)!).toNumber(),
      percentageChange(this.prices.at(-2)!, this.prices.at(-1)!).toNumber()
    ]
  }

  public performance (): BigNumber[] | undefined {
    if (this.prices.length < 2) { return undefined }
    const change = this.prices.at(-1)!.sub(this.prices.at(-2)!);
    const changeTimes = this.prices.at(-2)!.div(change);
    return [change, changeTimes];
  }
}

export function tokensToString () {
  let result = ''
  if (DEBUG)
    for (const t of tokens) { result += `${t.symbol} ${t.performance()} ${t.prices.toString()}\n` }
  else
    for (const t of tokens) { result += `${t.symbol} ${t.performance()} ${t.prices.at(-1)?.toString()}\n` }
  return result
}

export const WETH_TOKEN = new Token(
  '0xC02aaA39b223FE8D0A0e5C4F27eAD9083C756Cc2',
  18,
  'WETH',
  'Wrapped Ether'
)

export const USDC_TOKEN = new Token(
  '0xa0b86991c6218b36c1d19d4a2e9eb0ce3606eb48',
  6,
  'USDC',
  'USD//C'
)

export const TETHER_TOKEN = new Token(
  '0xdAC17F958D2ee523a2206206994597C13D831ec7',
  6,
  'USDT',
  'Tether'
)

export const BNB_TOKEN = new Token(
  '0xB8c77482e45F1F44dE1745F52C74426C631bDD52',
  18,
  'BNB',
  'BNB'
)

export const MATIC_TOKEN = new Token(
  '0x7D1AfA7B718fb893dB30A3aBc0Cfc608AaCfeBB0',
  18,
  'MATIC',
  'Polygon Matic'
)

export const OKB_TOKEN = new Token(
  '0x75231F58b43240C9718Dd58B4967c5114342a86c',
  18,
  'OKB',
  'OKB'
)

export const SHIB_TOKEN = new Token(
  '0x95aD61b0a150d79219dCF64E1E6Cc01f0B64C4cE',
  18,
  'SHIB',
  'Shiba Inu'
)

export const UNI_TOKEN = new Token(
  '0x1f9840a85d5aF5bf1D1762F925BDADdC4201F984',
  18,
  'UNI',
  'Uniswap'
)

export const THETA_TOKEN = new Token(
  '0x3883f5e181fccaF8410FA61e12b59BAd963fb645',
  18,
  'THETA',
  'Theta'
)

export const WBTC_TOKEN = new Token(
  '0x2260FAC5E5542a773Aa44fBCfeDf7C193bc2C599',
  8,
  'WBTC',
  'Wrapped Bitcoin'
)

export const LINK_TOKEN = new Token(
  '0x514910771AF9Ca656af840dff83E8264EcF986CA',
  18,
  'LINK',
  'Chainlink'
)

export const LDO_TOKEN = new Token(
  '0x5A98FcBEA516Cf06857215779Fd812CA3beF1B32',
  18,
  'LDO',
  'Lido DAO'
)

export const NEAR_TOKEN = new Token(
  '0x85F17Cf997934a597031b2E18a9aB6ebD4B9f6a4',
  24,
  'NEAR',
  'NEAR'
)

export const VEN_TOKEN = new Token(
  '0xD850942eF8811f2A866692A623011bDE52a462C1',
  18,
  'VEN',
  'VeChain'
)

export const APE_TOKEN = new Token(
  '0x4d224452801ACEd8B2F0aebE155379bb5D594381',
  18,
  'APE',
  'ApeCoin'
)

export const QNT_TOKEN = new Token(
  '0x4a220E6096B25EADb88358cb44068A3248254675',
  18,
  'QNT',
  'Quant'
)

export const CRO_TOKEN = new Token(
  '0xA0b73E1Ff0B80914AB6fe0444E65848C4C34450b',
  8,
  'CRO',
  'Cronos'
)

export const GRT_TOKEN = new Token(
  '0xc944E90C64B2c07662A292be6244BDf05Cda44a7',
  18,
  'GRT',
  'Graph'
)

export const FTM_TOKEN = new Token(
  '0x4E15361FD6b4BB609Fa63C81A2be19d873717870',
  18,
  'FTM',
  'Fantom'
)

export const SAND_TOKEN = new Token(
  '0x3845badAde8e6dFF049820680d1F14bD3903a5d0',
  18,
  'SAND',
  'SAND'
)

export const FRAX_TOKEN = new Token(
  '0x853d955aCEf822Db058eb8505911ED77F175b99e',
  18,
  'FRAX',
  'Frax'
)

export const RPL_TOKEN = new Token(
  '0xD33526068D116cE69F19A9ee46F0bd304F21A51f',
  18,
  'RPL',
  'Rocket Pool'
)

export const KCS_TOKEN = new Token(
  '0xf34960d9d60be18cC1D5Afc1A6F012A723a28811',
  6,
  'KCS',
  'KuCoin'
)

export const HT_TOKEN = new Token(
  '0x6f259637dcD74C767781E37Bc6133cd6A68aa161',
  18,
  'HT',
  'HuobiToken'
)

export const SNX_TOKEN = new Token(
  '0xC011a73ee8576Fb46F5E1c5751cA3B9Fe0af2a6F',
  18,
  'SNX',
  'Synthetix Network'
)

export const IMX_TOKEN = new Token(
  '0xF57e7e7C23978C3cAEC3C3548E3D615c346e79fF',
  18,
  'IMX',
  'Immutable X'
)

export const FXS_TOKEN = new Token(
  '0x3432B6A60D23Ca0dFCa7761B7ab56459D9C964D0',
  18,
  'FXS',
  'Frax Share'
)

export const CHZ_TOKEN = new Token(
  '0x3506424F91fD33084466F402d5D97f05F8e3b4AF',
  18,
  'CHZ',
  'chiliZ'
)

export const BIT_TOKEN = new Token(
  '0x1A4b46696b2bB4794Eb3D4c26f1c55F9170fa4C5',
  18,
  'BIT',
  'BitDAO'
)

export const FLOKI_TOKEN = new Token(
  '0xcf0C122c6b73ff809C693DB761e7BaeBe62b6a2E',
  9,
  'FLOKI',
  'FLOKI'
)

export const ENJ_TOKEN = new Token(
  '0xF629cBd94d3791C9250152BD8dfBDF380E2a3B9c',
  18,
  'ENJ',
  'Enjin'
)

export const AGIX_TOKEN = new Token(
  '0x5B7533812759B45C2B44C19e320ba2cD2681b542',
  8,
  'AGIX',
  'SingularityNET'
)

export const CVX_TOKEN = new Token(
  '0x4e3FBD56CD56c3e72c1403e103b45Db9da5B9D2B',
  18,
  'CVX',
  'Convex'
)

export const BLUR_TOKEN = new Token(
  '0x5283D291DBCF85356A21bA090E6db59121208b44',
  18,
  'BLUR',
  'Blur'
)

export const PAXG_TOKEN = new Token(
  '0x45804880De22913dAFE09f4980848ECE6EcbAf78',
  18,
  'PAXG',
  'Paxos Gold'
)

export const ONEINCH_TOKEN = new Token(
  '0x111111111117dC0aa78b770fA6A738034120C302',
  18,
  '1INCH',
  '1INCH'
)

export const BAT_TOKEN = new Token(
  '0x0D8775F648430679A709E98d2b0Cb6250d2887EF',
  18,
  'BAT',
  'Basic Attention'
)

export const COMP_TOKEN = new Token(
  '0xc00e94Cb662C3520282E6f5717214004A7f26888',
  18,
  'COMP',
  'Compound'
)

export const NEXO_TOKEN = new Token(
  '0xB62132e35a6c13ee1EE0f84dC5d40bad8d815206',
  18,
  'NEXO',
  'Nexo'
)

export const HOT_TOKEN = new Token(
  '0x6c6EE5e31d828De241282B9606C8e98Ea48526E2',
  18,
  'HOT',
  'HoloToken'
)

export const ONE_TOKEN = new Token(
  '0x799a4202c12ca952cB311598a024C80eD371a41e',
  18,
  'ONE',
  'HarmonyOne'
)

export const INJ_TOKEN = new Token(
  '0xe28b3B32B6c345A34Ff64674606124Dd5Aceca30',
  18,
  'INJ',
  'Injective'
)

export const SUSHI_TOKEN = new Token(
  '0x6B3595068778DD592e39A122f4f5a5cF09C90fE2',
  18,
  'SUSHI',
  'Sushi'
)

export const AMP_TOKEN = new Token(
  '0xfF20817765cB7f73d4bde2e66e067E58D11095C2',
  18,
  'AMP',
  'Amp'
)

export const RSR_TOKEN = new Token(
  '0x320623b8E4fF03373931769A31Fc52A4E78B5d70',
  18,
  'RSR',
  'Reserve Rights'
)

export const LRC_TOKEN = new Token(
  '0xBBbbCA6A901c926F240b89EacB641d8Aec7AEafD',
  18,
  'LRC',
  'LoopringCoin V2'
)

export const RNDR_TOKEN = new Token(
  '0x6De037ef9aD2725EB40118Bb1702EBb27e4Aeb24',
  18,
  'RNDR',
  'Render'
)

export const ZIL_TOKEN = new Token(
  '0x05f4a42e251f2d52b8ed15E9FEdAacFcEF1FAD27',
  12,
  'ZIL',
  'Zilliqa'
)

export const CHSB_TOKEN = new Token(
  '0xba9d4199faB4f26eFE3551D490E3821486f135Ba',
  8,
  'CHSB',
  'SwissBorg'
)

export const DAO_TOKEN = new Token(
  '0x0f51bb10119727a7e5eA3538074fb341F56B09Ad',
  18,
  'DAO',
  'DAO Maker'
)

export const OCEAN_TOKEN = new Token(
  '0x967da4048cD07aB37855c090aAF366e4ce1b9F48',
  18,
  'OCEAN',
  'Ocean'
)

export const SXP_TOKEN = new Token(
  '0x8CE9137d39326AD0cD6491fb5CC0CbA0e089b6A9',
  18,
  'SXP',
  'Swipe'
)

export const TEL_TOKEN = new Token(
  '0x467Bccd9d29f223BcE8043b84E8C8B282827790F',
  2,
  'TEL',
  'Telcoin'
)

export const ACH_TOKEN = new Token(
  '0xEd04915c23f00A313a544955524EB7DBD823143d',
  8,
  'ACH',
  'Alchemy'
)

export const POLY_TOKEN = new Token(
  '0x9992eC3cF6A55b00978cdDF2b27BC6882d88D1eC',
  18,
  'POLY',
  'Polymath'
)

export const ILV_TOKEN = new Token(
  '0x767FE9EDC9E0dF98E07454847909b5E959D7ca0E',
  18,
  'ILV',
  'Illuvium'
)

export const STG_TOKEN = new Token(
  '0xAf5191B0De278C7286d6C7CC6ab6BB8A73bA2Cd6',
  18,
  'STG',
  'Stargate'
)

export const METIS_TOKEN = new Token(
  '0x9E32b13ce7f2E80A01932B42553652E053D6ed8e',
  18,
  'METIS',
  'Metis'
)

export const API3_TOKEN = new Token(
  '0x0b38210ea11411557c13457D4dA7dC6ea731B88a',
  18,
  'API3',
  'API3'
)

export const TRAC_TOKEN = new Token(
  '0xaA7a9CA87d3694B5755f213B5D04094b8d0F0A6F',
  18,
  'TRAC',
  'Trace'
)

export const RLC_TOKEN = new Token(
  '0x607F4C5BB672230e8672085532f7e901544a7375',
  9,
  'RLC',
  'RLC'
)

export const GTC_TOKEN = new Token(
  '0x6De037ef9aD2725EB40118Bb1702EBb27e4Aeb24',
  18,
  'GTC',
  'Gitcoin'
)

export const DUSK_TOKEN = new Token(
  '0x940a2dB1B7008B6C776d4faaCa729d6d4A4AA551',
  18,
  'DUSK',
  'Dusk Network'
)

export const STORJ_TOKEN = new Token(
  '0xB64ef51C888972c908CFacf59B47C1AfBC0Ab8aC',
  8,
  'STORJ',
  'Storj'
)

export const REEF_TOKEN = new Token(
  '0xFE3E6a25e6b192A42a44ecDDCd13796471735ACf',
  18,
  'REEF',
  'Reef Finance'
)

export const CEEK_TOKEN = new Token(
  '0xb056c38f6b7Dc4064367403E26424CD2c60655e1',
  18,
  'CEEK',
  'CEEK'
)

export const BNT_TOKEN = new Token(
  '0x1F573D6Fb3F13d689FF844B4cE37794d79a7FF1C',
  18,
  'BNT',
  'Bancor'
)

export const tokens = [
  HT_TOKEN,
  AMP_TOKEN,
  APE_TOKEN,
  BAT_TOKEN,
  BIT_TOKEN,
  BNB_TOKEN,
  CHZ_TOKEN,
  CRO_TOKEN,
  CVX_TOKEN,
  ENJ_TOKEN,
  FTM_TOKEN,
  FXS_TOKEN,
  GRT_TOKEN,
  HOT_TOKEN,
  IMX_TOKEN,
  INJ_TOKEN,
  KCS_TOKEN,
  LDO_TOKEN,
  LRC_TOKEN,
  OKB_TOKEN,
  ONE_TOKEN,
  QNT_TOKEN,
  RPL_TOKEN,
  RSR_TOKEN,
  SNX_TOKEN,
  UNI_TOKEN,
  VEN_TOKEN,
  ZIL_TOKEN,
  AGIX_TOKEN,
  BLUR_TOKEN,
  COMP_TOKEN,
  FRAX_TOKEN,
  LINK_TOKEN,
  NEAR_TOKEN,
  NEXO_TOKEN,
  PAXG_TOKEN,
  RNDR_TOKEN,
  SAND_TOKEN,
  SHIB_TOKEN,
  USDC_TOKEN,
  WBTC_TOKEN,
  WETH_TOKEN,
  FLOKI_TOKEN,
  MATIC_TOKEN,
  SUSHI_TOKEN,
  THETA_TOKEN,
  TETHER_TOKEN,
  ONEINCH_TOKEN,
  CHSB_TOKEN,
  DAO_TOKEN,
  OCEAN_TOKEN,
  SXP_TOKEN,
  TEL_TOKEN,
  ACH_TOKEN,
  POLY_TOKEN,
  ILV_TOKEN,
  STG_TOKEN,
  METIS_TOKEN,
  API3_TOKEN,
  TRAC_TOKEN,
  RLC_TOKEN,
  GTC_TOKEN,
  DUSK_TOKEN,
  STORJ_TOKEN,
  REEF_TOKEN,
  CEEK_TOKEN,
  BNT_TOKEN,
] // ~68

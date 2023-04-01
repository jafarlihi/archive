export let log = ''

export const appendLog = (l: string) => {
  log += l + '\n'
}

export const clearLog = () => {
  log = ''
}

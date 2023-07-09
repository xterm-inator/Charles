export interface Stats {
  fps: number,
  cpu_temp: number,
  gpu_temp: number,
}

export const DefaultStats: Stats = {
  fps: 0,
  cpu_temp: 0,
  gpu_temp: 0,
}

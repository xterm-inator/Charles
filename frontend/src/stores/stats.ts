import { defineStore } from 'pinia'
import { http } from '@/utils'
import { clone } from 'lodash'
import { DefaultStats } from '@/models/stats.model'
import type { Stats } from '@/models/stats.model'
import type { AxiosResponse } from 'axios'

export const useStatsStore = defineStore({
  id: 'stats',
  state: (): {stats: Stats} => ({
    stats: clone(DefaultStats),
  }),

  getters: {
  },

  actions: {
    async getStats(): Promise<AxiosResponse> {
      const response = await http.get('stats')
      this.stats = response.data
      return response
    },

    resetStats(): void {
      this.stats = clone(DefaultStats)
    }
  }
})

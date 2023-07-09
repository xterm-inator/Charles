<template>
  <div class="container-xl d-flex flex-column justify-content-center">
    <div class="row row-cards">
      <stats-card class="col-md-6 col-xl-3" title="Vision FPS" :value="stats.fps"></stats-card>
      <stats-card class="col-md-6 col-xl-3" title="CPU Temp" :value="stats.cpu_temp"></stats-card>
      <stats-card class="col-md-6 col-xl-3" title="GPU Temp" :value="stats.gpu_temp"></stats-card>
      <div class="col-9">
        <div class="card card-sm">
          <img :src="currentImage" alt="" class="card-img">
        </div>
      </div>
    </div>
  </div>
</template>
<script setup lang="ts">
import { useStatsStore } from '@/stores/stats'
import { computed, onMounted, onBeforeUnmount, ref } from 'vue'
import StatsCard from '@/components/StatsCard.vue'

const statsStore = useStatsStore()

const stats = computed(() => statsStore.stats)

const currentImage = ref();

let interval: ReturnType<typeof setInterval>

onMounted(() => {
  interval = setInterval(() => {
    statsStore.getStats()
  }, 1000)
})

onBeforeUnmount(() => {
  clearInterval(interval)
})

const ws = new WebSocket('ws://10.0.0.15:8000/echo/video_feed')
ws.onmessage = onMessage

function onMessage(event: any): void {
  currentImage.value = 'data:image/bmp;base64,' + event.data
}
</script>

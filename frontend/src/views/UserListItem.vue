<template>
  <tr>
    <td>
      {{ props.user.email }}
    </td>
    <td class="text-right">
      <button class="btn btn-danger btn-sm pull-right" @click="handleDelete">Delete</button>
    </td>
  </tr>
</template>
<script setup lang="ts">
import { useUserStore } from '@/stores/user'
import swal from 'sweetalert'
import type { User } from '@/models/user.model'

interface Props {
  user: User
}

const props = defineProps<Props>()
const userStore = useUserStore();

async function handleDelete(): Promise<void> {
  const response = await swal({
    title: 'Are you sure?',
    text: '',
    icon: 'warning',
    buttons: {
      cancel: true,
      ok: {
        text: 'Yes',
        className: 'swal-button--danger',
        closeModal: false
      }
    },
    dangerMode: true
  })
  if (response && props.user.id) {
    await userStore.deleteUser(props.user.id)
    if (swal.stopLoading && swal.close) {
      swal.stopLoading()
      swal.close()
    }
  }
}
</script>

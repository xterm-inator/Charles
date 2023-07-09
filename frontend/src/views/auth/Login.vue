<template>
  <div class="card card-md">
    <div class="card-body">
      <h2 class="card-title text-center mb-4">Login to your account</h2>
      <div class="d-grid mt-3">
        <form>
          <div class="mb-3">
            <label class="form-label">Email address</label>
            <input
                type="email"
                class="form-control"
                placeholder="your@email.com"
                autocomplete="off"
                v-model="email"
                :class="{ 'is-invalid': errors.email }"
            >
            <div class="invalid-feedback" v-if="errors.email">{{ errors.email }}</div>
          </div>
          <div class="mb-3">
            <label class="form-label">Password</label>
            <input
                type="password"
                class="form-control"
                placeholder="Your password"
                autocomplete="off"
                v-model="password"
                :class="{ 'is-invalid': errors.password }"
            >
            <div class="invalid-feedback" v-if="errors.password">{{ errors.password }}</div>
          </div>

          <div class="form-footer">
            <async-button class="btn btn-primary w-100" @click="handleLogin">Sign In</async-button>
          </div>
        </form>
      </div>
    </div>
  </div>
</template>
<script setup lang="ts">
import { useRouter } from 'vue-router'
import { toFormValidator } from '@vee-validate/zod'
import { useField, useForm } from 'vee-validate'
import * as zod from 'zod'
import { useAuthStore } from '@/stores/auth'

const router = useRouter()
const store = useAuthStore()

const validationSchema = toFormValidator(
    zod.object({
      email: zod.string().min(1).email(),
      password: zod.string()
    })
)

const { handleSubmit, errors, values, handleReset } = useForm({
  validationSchema,
});

const { value: email } = useField<string>('email')
const { value: password } = useField<string>('password')

const handleLogin = handleSubmit(async ({ email, password }, { setErrors }) => {
  try {
    await store.login({ email, password })
    router.push({ name: 'dashboard' })
  } catch (e: any) {
    console.error(e)
    if (e.response.status === 422) {
      setErrors(e.response.data.errors)
    }
  }
})
</script>

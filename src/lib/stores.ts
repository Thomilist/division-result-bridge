import { persisted } from "svelte-persisted-store";

export const theme = persisted("theme", "system");
import { persisted } from "svelte-persisted-store";

export const theme = persisted("theme", "system");
export const language = persisted("language", "system");
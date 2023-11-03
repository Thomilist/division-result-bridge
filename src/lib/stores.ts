import { persisted } from "svelte-persisted-store";
import { writable } from "svelte/store";
import type { Release } from "./types";

export const theme = persisted("theme", "system");
export const language = persisted("language", "system");

export const releases = writable<Release[]>([]);
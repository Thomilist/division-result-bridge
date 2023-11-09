import { persisted } from "svelte-persisted-store";
import { writable } from "svelte/store";
import type { DocPath, Release } from "./types";

export const theme = persisted("theme", "system");
export const language = persisted("language", "system");

export const releases = writable<Release[]>([]);

export const docpath = writable<DocPath>({collection: "", page: ""});
export const title = writable<string>("");
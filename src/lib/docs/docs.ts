import type { DocCollectionSpec, DocPageProps } from "$lib/types";
import Configuration from "./getting-started/Configuration.svelte";
import CreateCompetition from "./getting-started/CreateCompetition.svelte";
import Installation from "./getting-started/Installation.svelte";
import Prerequisites from "./getting-started/Prerequisites.svelte";
import Introduction from "./preface/Introduction.svelte";

// Translation key for a doc collection
export function tcol(props: DocPageProps, suffix?: string[]): string
{
    return [`page.docs.collection.${props.collection}`, ...(suffix ? suffix : [])].join(".");
}

// Translation key for a doc page
export function tpage(props: DocPageProps, suffix?: string[]): string
{
    return tcol(props, [`page.${props.title}`, ...(suffix ? suffix : [])]);
}

// Doc collections and pages
export const docs: DocCollectionSpec[] =
[
    {
        title: "preface",
        connected: true,
        pages:
        [
            {
                title: "introduction",
                component: Introduction
            }
        ]
    },
    {
        title: "getting-started",
        connected: true,
        pages:
        [
            {
                title: "prerequisites",
                component: Prerequisites
            },
            {
                title: "installation",
                component: Installation
            },
            {
                title: "create-competition",
                component: CreateCompetition
            },
            {
                title: "configuration",
                component: Configuration
            }
        ]
    }
];
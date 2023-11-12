import type { DocPageProps } from "$lib/types";

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
export const docs =
{
    collections:
    {
        preface:
        {
            name: "preface",
            pages:
            {
                introduction:
                {
                    name: "introduction"
                }
            }
        },
        getting_started:
        {
            name: "getting-started",
            pages:
            {
                installation:
                {
                    name: "installation"
                },
                prerequisites:
                {
                    name: "prerequisites"
                }
            }
        }
    }
};
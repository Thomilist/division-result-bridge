import Installation from "$lib/docs/getting-started/Installation.svelte";
import Prerequisites from "$lib/docs/getting-started/Prerequisites.svelte";
import Introduction from "$lib/docs/preface/Introduction.svelte";
import type { DocCollection, DocCollectionSpec, DocPage, DocPageProps, DocPageSpec } from "$lib/types";
import type { LayoutLoad } from "./$types";

const page_specs: DocCollectionSpec[] =
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
            }
        ]
    }
];

export const load: LayoutLoad = () =>
{
    const doc_entries = page_specs.map((page): [string, DocCollection] =>
    {
        return [page.title, createCollection(page)];
    });
    
    return {
        docs: new Map(doc_entries)
    };
};

function createPage(collection: string, spec: DocPageSpec): DocPage
{
    const props: DocPageProps =
    {
        title: spec.title,
        collection: collection
    };

    const page: DocPage =
    {
        component: spec.component,
        props: props
    };

    return page;
}

function createCollection(spec: DocCollectionSpec): DocCollection
{
    let collection: DocCollection =
    {
        title: spec.title,
        connected: spec.connected,
        pages: new Map(spec.pages.map((page) =>
        {
            return [page.title, createPage(spec.title, page)];
        }))
    };

    if (spec.connected)
    {
        const pages = Array.from(collection.pages.keys());

        for (let i = 0; i < pages.length; i++)
        {
            let previous: string | undefined = undefined;
            const current: string | undefined = pages.at(i);
            let next: string | undefined = undefined;

            if (!current)
            {
                continue;
            }
            
            if (i > 0)
            {
                previous = pages.at(i - 1);
            }

            if (i < (pages.length - 1))
            {
                next = pages.at(i + 1);
            }

            let page = collection.pages.get(current);

            if (!page)
            {
                continue;
            }

            page.props.previous = previous;
            page.props.next = next;

            collection.pages.set(current, page);
        }
    }

    return collection;
}
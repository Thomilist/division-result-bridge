<script lang="ts">
	import { docpath } from "$lib/stores";
	import type { HeaderHierarchy } from "$lib/types";
	import { onMount, tick } from "svelte";
	import DocPageNavList from "./DocPageNavList.svelte";
	import { locale, t } from "svelte-intl-precompile";

    let index = 0;

    const header_depths = new Map(Object.entries
    ({
        H1: 1,
        H2: 2,
        H3: 3,
        H4: 4,
        H5: 5,
        H6: 6
    }));

    let header_hierarchy: HeaderHierarchy[] = [];

    function findHeaders(): NodeList
    {
        return document.querySelectorAll(".doc-content-container :is(h1, h2, h3, h4, h5, h6)");
    }

    function headerDepth(header: Node): number
    {
        const depth = header_depths.get(header.nodeName);
        return depth ? depth : 0;
    }

    function constructHeaderHierarchy(headers: NodeList, depth: number): HeaderHierarchy[]
    {
        let hierarchies: HeaderHierarchy[] = [];
        
        while (index < headers.length)
        {
            const header = headers[index];
            const new_depth = headerDepth(header);

            if (new_depth < depth)
            {
                return hierarchies;
            }

            index++;

            const hierarchy: HeaderHierarchy =
            {
                node: header,
                children: constructHeaderHierarchy(headers, depth + 1)
            };

            hierarchies.push(hierarchy);
        }

        return hierarchies;
    }

    let updatePageNav = () => {};
    $: $docpath, updatePageNav();
    $: $locale, updatePageNav();

    let observer: IntersectionObserver;
    let page_nav_links = new Map<string, Element>();

    function initialiseObserver()
    {
        const options =
        {
            root: null,
            rootMargin: "-200px 0px 0px 0px",
            threshold: 1
        };

        observer = new IntersectionObserver(updateNavHighlight, options);
    }

    function startNavHighlighter(headers: NodeList)
    {
        headers.forEach((header) =>
        {
            if (header instanceof Element)
            {
                observer.observe(header);
            }
        });

        const page_nav_items = document.querySelectorAll(".doc-page-nav a");

        page_nav_items.forEach((nav_item) =>
        {
            const href = nav_item.getAttribute("href")
            
            if (href)
            {
                page_nav_links.set(href, nav_item);
            }
        });
    }

    function stopNavHighlighter()
    {
        observer.disconnect();
        header_positions.clear();
        page_nav_links.clear();
    }

    let header_positions = new Map<string, number>();
    const class_highlightable = "doc-page-nav-highlightable";
    const class_highlighted = "doc-page-nav-highlighted";

    const updateNavHighlight: IntersectionObserverCallback = (entries, observer) =>
    {
        // First run (at page load) has no direction
        if (header_positions.size === 0)
        {
            entries.forEach((entry) =>
            {
                header_positions.set(entry.target.id, entry.boundingClientRect.y);
            });

            for (const entry of entries)
            {
                if (!entry.isIntersecting)
                {
                    addHighlightableClass(entry.target);
                }
                else
                {
                    break;
                }
            }

            setHighlightedPageNavlink();

            return;
        }
        
        // Subsequent observer callbacks
        entries.forEach((entry) =>
        {
            const old_position = (() =>
            {
                const position = header_positions.get(entry.target.id);
                return position ? position : 0;
            })();
            const new_position = entry.boundingClientRect.y;
            
            // Scroll down
            if (new_position < old_position)
            {
                // Enter page from below
                if (entry.isIntersecting)
                {
                    // Do nothing
                }
                // Leave page at the top
                else
                {
                    addHighlightableClass(entry.target);
                }
            }
            // Scroll up
            else if (new_position > old_position)
            {
                // Enter page from above
                if (entry.isIntersecting)
                {
                    removeHighlightableClass(entry.target);
                }
                // Leave page at the bottom
                else
                {
                    // Do nothing
                }
            }
            // No scroll, but visibility can change on viewport resizing
            else
            {
                // Enter page from below
                if (entry.isIntersecting)
                {
                    // Do nothing
                }
                // Leave page at the bottom
                else
                {
                    // Do nothing
                }
            }

            header_positions.set(entry.target.id, new_position);
        });

        setHighlightedPageNavlink();
    };

    function findPageNavLink(header_element: Element): Element | undefined
    {
        return page_nav_links.get(`#${header_element.id}`);
    }

    function addHighlightableClass(header_element: Element)
    {
        findPageNavLink(header_element)?.classList.add(class_highlightable);
    }

    function removeHighlightableClass(header_element: Element)
    {
        findPageNavLink(header_element)?.classList.remove(class_highlightable);
    }

    function setHighlightedPageNavlink()
    {
        const elements = Array.from(page_nav_links.values());
        
        elements.forEach((element) =>
        {
            element.classList.remove(class_highlighted);
        });

        elements.findLast((element) => element.classList.contains(class_highlightable))?.classList.add(class_highlighted);
    }

    onMount(() =>{
        initialiseObserver();
        
        updatePageNav = async () =>
        {
            stopNavHighlighter();
            
            await tick();
            
            index = 0;
            const headers = findHeaders();
            header_hierarchy = constructHeaderHierarchy(headers, 1);
            
            await tick();

            startNavHighlighter(headers);
        };

        return () =>
        {
            stopNavHighlighter();
        };
    });
</script>

<style lang="scss">
    @import "$styles/doc-page-nav.scss";
</style>

<div class="doc-page-nav">
    <nav>
        <h2 class="doc-collection-label">
            {$t("page.docs.nav.on-this-page")}
        </h2>

        <DocPageNavList props={{headers: header_hierarchy}}/>
    </nav>
</div>
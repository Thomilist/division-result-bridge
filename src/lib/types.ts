import type { DateTime } from "luxon";

// Theme

export type Theme = "system" | "light" | "dark" | "oled";

// Navigation

export type NavPropsBase =
{
    label: string
};

export type NavHomeProps = NavPropsBase &
{
    route: string,
    icon?:
    {
        component: any,
        size: number
    }
};

export type NavLinkProps = NavPropsBase &
{
    route: string,
    skip_translation?: boolean,
    exclude_base?: boolean
};

export type NavDropdownProps = NavPropsBase &
{
    align: "left" | "right",
    expand: "click" | "hover",
    icon?: any,
    items: NavItem[]
};

export type LanguageSelectProps = NavPropsBase & {};
export type ThemeSwitchProps = NavPropsBase & {};

export type NavItem =
{
    component: any,
    props: NavPropsBase
        | NavLinkProps
        | NavDropdownProps
        | LanguageSelectProps
        | ThemeSwitchProps
};

export type NavBarProps =
{
    home: NavHomeProps,
    items: NavItem[],
    options: NavDropdownProps
};

// Releases

export type Release =
{
    tag: string,
    draft: boolean,
    prerelease: boolean,
    link: string,
    published_at: DateTime,
    text: string,
    assets: Asset[]
};

export type Asset =
{
    name: string,
    download_link: string,
    download_count: number,
    size: number
};

export type ReleaseMeta =
{
    version:
    {
        full: string,
        major: number,
        minor: number,
        patch: number
    },
    assets: AssetMeta[]
};

export type AssetMeta =
{
    platform: string,
    arch: string,
    format: string,
    size:
    {
        bytes: number,
        pretty: string
    }
};

export interface ReleaseJson
{
    tag_name: string,
    draft: boolean,
    prerelease: boolean,
    html_url: string,
    published_at: string,
    body: string,
    assets: AssetsJson[]
};

export function isReleaseJson(obj: any): obj is ReleaseJson
{
    return true
        && "tag_name" in obj
        && "draft" in obj
        && "prerelease" in obj
        && "html_url" in obj
        && "published_at" in obj
        && "body" in obj
        && "assets" in obj
        && Array.isArray(obj.assets);
}

export interface AssetsJson
{
    name: string,
    browser_download_url: string,
    download_count: number,
    size: number
};

export function isAssetsJson(obj: any): obj is AssetsJson
{
    return true
        && "name" in obj
        && "browser_download_url" in obj
        && "download_count" in obj
        && "size" in obj;
}

// Documentation

export type DocPageSpec =
{
    title: string,
    component: any
};

export type DocPage =
{
    component: any,
    props: DocPageProps
};

export type DocPageProps =
{
    title: string,
    collection: string,
    previous?: string,
    next?: string
};

export type DocCollectionSpec =
{
    title: string,
    connected: boolean,
    pages: DocPageSpec[]
};

export type DocCollection =
{
    title: string,
    connected: boolean,
    pages: Map<string, DocPage>
};

export type DocPath =
{
    collection: string,
    page: string
};

export type HeaderHierarchy =
{
    node: Node,
    children: HeaderHierarchy[]
};

export type DocPageNavListProps =
{
    headers: HeaderHierarchy[]
}

export type DocHeaderProps =
{
    depth: 0 | 1 | 2 | 3 | 4 | 5 | 6,
    specifiers: string[],
    docpage: DocPageProps,
    values?: any
};

export type DocFooterProps =
{
    collection: DocCollection | undefined
};

export type DocElementProps =
{
    element?: string,
    docpage: DocPageProps,
    specifiers: string[],
    values?: any
}

// Image

export type ImageProps =
{
    src: string,
    alt: string,
    caption?: string
};
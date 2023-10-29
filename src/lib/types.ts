type NavPropsBase =
{
    label: string
};

type NavHomeProps = NavPropsBase &
{
    route: string,
    icon?:
    {
        component: any,
        size: number
    }
};

type NavLinkProps = NavPropsBase &
{
    route: string
};

type NavDropdownProps = NavPropsBase &
{
    align: "left" | "right",
    expand: "click" | "hover",
    icon?: any,
    items: NavItem[]
};

type LanguageSelectProps = NavPropsBase & {};
type ThemeSwitchProps = NavPropsBase & {};

type NavItem =
{
    component: any,
    props: NavPropsBase
        | NavLinkProps
        | NavDropdownProps
        | LanguageSelectProps
        | ThemeSwitchProps
};
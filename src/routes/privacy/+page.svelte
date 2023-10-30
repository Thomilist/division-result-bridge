<script lang="ts">
    import { t } from "svelte-intl-precompile";
</script>

<svelte:head>
    <title>
        {$t("page.privacy.title")} - {$t("project.name")}
    </title>
</svelte:head>

<h1>
    {$t("page.privacy.title")}
</h1>

<p>
    {$t("page.privacy.intro")}
</p>

<p>
    {@html $t("page.privacy.tldr")}
</p>

<h2>
    {$t("page.privacy.website.title")}
</h2>

<p>
    {@html $t("page.privacy.website.content")}
</p>

<h2>
    {$t("page.privacy.application.title")}
</h2>

<p>
    {@html $t("page.privacy.application.settings")}
</p>

<p>
    {@html $t("page.privacy.application.results")}
</p>
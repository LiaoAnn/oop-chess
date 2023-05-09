import { type GlobalThemeOverrides } from 'naive-ui';
import { computed, ref } from 'vue';

export default function useTheme() {
  const primaryColor = '#764e30';
  const secondaryColor = '#d9a669';
  type Theme = null | 'dark';
  const theme = ref<Theme>(null);

  const baseThemeOverrides: GlobalThemeOverrides = {
    common: {
      primaryColor: primaryColor,
      primaryColorHover: primaryColor,
      primaryColorPressed: primaryColor,
      primaryColorSuppl: primaryColor,
      fontWeightStrong: '600',
    },
  };

  const lightThemeOverrides: GlobalThemeOverrides = {
    ...baseThemeOverrides,
    common: {
      ...baseThemeOverrides.common,
    },
  };

  const darkThemeOverrides: GlobalThemeOverrides = {
    ...baseThemeOverrides,
    common: {
      ...baseThemeOverrides.common,
    },
  };

  const themeOverrides = computed(() => {
    return theme.value === 'dark' ? darkThemeOverrides : lightThemeOverrides;
  });

  const toggleTheme = () => {
    theme.value = theme.value === 'dark' ? null : 'dark';
  };

  return {
    primaryColor,
    secondaryColor,
    theme,
    themeOverrides,
    toggleTheme,
  };
}

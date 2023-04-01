import React from 'react';
import {
  Card,
  Spacer,
  Button,
  Text,
  Navbar,
  Input,
  Row,
  Checkbox,
  Container,
} from '@nextui-org/react';
import { useTheme as useNextTheme } from 'next-themes'
import { Switch, useTheme } from '@nextui-org/react'
import { SunIcon } from '../icons/Sun';
import { useRouter } from 'next/router';

export default function Authentication(props: any) {
  const { setTheme } = useNextTheme();
  const { isDark, type, theme } = useTheme();
  const router = useRouter();

  return (
  <div>
        <Navbar isCompact isBordered variant="sticky">
        <Navbar.Brand>
          <Text b color="inherit" hideIn="xs">
          speechwave
          </Text>
        </Navbar.Brand>
        <Navbar.Content hideIn="xs" variant="underline">
        </Navbar.Content>
        <Navbar.Content>
              <Switch
              icon={<SunIcon />}
        checked={isDark}
        onChange={(e) => setTheme(e.target.checked ? 'dark' : 'light')}
      />
        </Navbar.Content>
      </Navbar>
    <div>
    {React.cloneElement(props.children, { theme })}
    </div>
    </div>
  );
}

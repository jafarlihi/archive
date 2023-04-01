import Head from "next/head"
import React, { Suspense } from "react"
import { useRouter } from "next/router";
import { useTheme as useNextTheme } from 'next-themes'
import { BlitzLayout } from "@blitzjs/next"
import { useMutation } from "@blitzjs/rpc";
import { Switch, useTheme } from '@nextui-org/react'
import {
  Text,
  Navbar,
  Button,
  Badge,
  Spacer,
} from '@nextui-org/react';
import { useCurrentUser } from "src/users/hooks/useCurrentUser";
import logout from "src/auth/mutations/logout";
import { BsSun } from 'react-icons/bs';
import { BiCartAlt, BiLogOut } from 'react-icons/bi';
import { AiOutlineApi } from 'react-icons/ai';

const UserInfo = () => {
  const currentUser = useCurrentUser();

  if (!currentUser) return <></>;
  return (
    <div style={{ display: 'flex', alignItems: 'center' }}>
      <Badge isSquared color="primary" variant="bordered">
        {currentUser?.email}
      </Badge>
      <Spacer x={0.5} />
      <Badge isSquared color="primary" variant="bordered">
        0 credits
      </Badge>
    </div>
  );
};

const UserButtons = () => {
  const currentUser = useCurrentUser();

  if (!currentUser) return <></>;
  return (
    <div style={{ display: 'flex', alignItems: 'center' }}>
      <Button iconRight={<BiCartAlt fill="currentColor"/>} color="primary" auto flat size="sm" onClick={
          async () => {
          }
      }>
        Buy credits
      </Button>
      <Spacer x={0.5}/>
      <Button iconRight={<AiOutlineApi fill="currentColor"/>} color="primary" auto flat size="sm" onClick={
          async () => {
          }
      }>
        API
      </Button>
    </div>
  );
};


const UserLogoutButton = () => {
  const currentUser = useCurrentUser();
  const router = useRouter();
  const [logoutMutation] = useMutation(logout);

  if (!currentUser) return <></>;
  return (
    <div style={{ display: 'flex', alignItems: 'center' }}>
      <Button iconRight={<BiLogOut fill="currentColor" style = {{ transform: 'rotate(180deg)' }}/>} color="error" auto flat size="sm" onClick={
          async () => {
            await logoutMutation();
            router.push('/');
          }
      }>
        Log out
      </Button>
    </div>
  );
};


const Layout: BlitzLayout<{title?: string; children?: React.ReactNode}> = ({title, children}) => {
  const { setTheme } = useNextTheme();
  const { isDark, theme } = useTheme();

  return (
    <div>
      <Head>
        <title>{title || "sw3"}</title>
        <link rel="icon" href="/favicon.ico" />
      </Head>
      <Navbar isCompact variant="sticky" maxWidth="fluid">
        <Navbar.Brand hideIn={'xs'}>
          <Text b color="inherit">
            speechwave
          </Text>
          <Spacer x={2}/>
          <Suspense>
            <UserInfo/>
          </Suspense>
        </Navbar.Brand>
        <Navbar.Content>
          <Switch
            icon={<BsSun/>}
            checked={isDark}
            onChange={(e) => setTheme(e.target.checked ? 'dark' : 'light')}
          />
          <div style={{ borderLeft: '1px solid ' + theme.colors.gray300.value, height: '100%' }}></div>
          <Suspense>
            <UserButtons/>
          </Suspense>
          <div style={{ borderLeft: '1px solid ' + theme.colors.gray300.value, height: '100%' }}></div>
          <Suspense>
            <UserLogoutButton/>
          </Suspense>
        </Navbar.Content>
      </Navbar>
      <div>
        <Suspense>
          {React.cloneElement(children as React.ReactElement, { theme })}
        </Suspense>
      </div>
    </div>
  )
}

export default Layout

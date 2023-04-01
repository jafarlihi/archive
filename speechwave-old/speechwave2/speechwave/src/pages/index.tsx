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
  const router = useRouter();

  return (
    <div>
      <Container
        display="flex"
        alignItems="center"
        justify="center"
        css={{ minHeight: '100vh' }}
      >
        <Card css={{ mw: '420px', p: '20px' }} variant="bordered">
          <Input
            clearable
            bordered            
            fullWidth
            color="primary"
            size="lg"
            placeholder="Email"
          />
          <Spacer y={1} />
          <Input
            clearable
            bordered
            fullWidth
            color="primary"
            size="lg"
            placeholder="Password"
            css={{ mb: '6px' }}
          />

          <Spacer y={1} />
          <Row justify="space-between">
            <Checkbox>
              <Text size={14}>Remember me</Text>
            </Checkbox>
            <Text size={14}>Forgot password?</Text>
          </Row>
          <Spacer y={1} />
                  <Button shadow color="primary" auto>
                  Sign in
        </Button>
          <Spacer y={1} />
          <h6 style={{ width: '100%', 
   textAlign: 'center',
   borderBottom: '1px solid ' + props.theme.colors.border.value,
   lineHeight: '0.1em',
   fontWeight: 'normal',
   margin: '10px 0 20px',  }}><span style={{     background: props.theme.colors.backgroundContrast.value,
    padding:'0 10px'  }}>or</span></h6>
    <Spacer y={0.5} />
            <Button shadow color="secondary" auto onClick={() => router.push('/signup')}>
            Sign up
        </Button>
        </Card>
      </Container>
    </div>
  );
}

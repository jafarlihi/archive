import { useRouter } from 'next/router';
import { BlitzPage } from "@blitzjs/next"
import { useMutation } from '@blitzjs/rpc';
import { AuthenticationError } from 'blitz';
import { Form, FORM_ERROR } from 'src/core/components/Form';
import {
  Card,
  Spacer,
  Button,
  Text,
  Row,
  Checkbox,
  Container,
} from '@nextui-org/react';
import { Login } from 'src/auth/validations';
import login from 'src/auth/mutations/login';
import { useCurrentUser } from 'src/users/hooks/useCurrentUser';
import LabeledTextField from 'src/core/components/LabeledTextField';

export const SignIn = (props: any) => {
  const router = useRouter();
  const [loginMutation] = useMutation(login);

  return (
    <div>
      <Container
        display="flex"
        alignItems="center"
        justify="center"
        css={{ minHeight: '100vh' }}
      >
        <Card css={{ mw: '420px', p: '20px' }} variant="bordered">
          <Form
            schema={Login}
            initialValues={{ email: '', password: '' }}
            onSubmit={async (values) => {
              try {
                await loginMutation(values);
                router.push('/');
              } catch (error: any) {
                if (error instanceof AuthenticationError) {
                  return { [FORM_ERROR]: "Given credentials are invalid" }
                } else {
                  return { [FORM_ERROR]: "Unexpected error encountered, please try again" }
                }
              }
            }}
          >
            <div style={{ marginBottom: '20px' }}>
              <LabeledTextField name="email" size="lg" clearable bordered fullWidth color="primary" placeholder="Email"/>
            </div>
            <LabeledTextField name="password" placeholder="Password" size="lg" clearable bordered fullWidth color="primary" type="password"/>
            <Spacer y={1}/>
            <Row justify="space-between">
              <Checkbox>
                <Text size={14}>Remember me</Text>
              </Checkbox>
              <Text size={14}>Forgot password?</Text>
            </Row>
            <Spacer y={1}/>
            <Button shadow color="primary" auto style={{ width: '100%' }} type="submit">
              Sign in
            </Button>
          </Form>
          <Spacer y={1}/>
          <h6 style={{ width: '100%', textAlign: 'center', borderBottom: '1px solid ' + props.theme.colors.border.value, lineHeight: '0.1em', fontWeight: 'normal', margin: '10px 0 20px' }}>
            <span style={{ background: props.theme.colors.backgroundContrast.value, padding: '0 10px' }}>
              or
            </span>
          </h6>
          <Spacer y={0.5}/>
          <Button shadow color="secondary" auto onClick={() => router.push('/register')}>
            Sign up
          </Button>
        </Card>
      </Container>
    </div>
  );
};

const SignInPage: BlitzPage = (props: any) => {
  const currentUser = useCurrentUser();
  const router = useRouter();

  if (currentUser) router.push('/');

  return <SignIn {...props} />;
}

export default SignInPage;

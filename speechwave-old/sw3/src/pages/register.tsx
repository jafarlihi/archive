import { useRouter } from 'next/router';
import { BlitzPage } from "@blitzjs/next"
import { useMutation } from '@blitzjs/rpc';
import { Form, FORM_ERROR } from 'src/core/components/Form';
import {
  Card,
  Spacer,
  Button,
  Container,
} from '@nextui-org/react';
import signup from 'src/auth/mutations/signup';
import { useCurrentUser } from 'src/users/hooks/useCurrentUser';
import { Signup } from 'src/auth/validations';
import LabeledTextField from 'src/core/components/LabeledTextField';

const SignUp = (props: any) => {
  const router = useRouter();
  const [signupMutation] = useMutation(signup);

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
            schema={Signup}
            initialValues={{ email: '', password: '' }}
            onSubmit={async (values) => {
              try {
                await signupMutation(values);
                router.push('/');
              } catch (error: any) {
                if (error.code === "P2002" && error.meta?.target?.includes("email")) {
                  return { email: "Email is already in use" }
                } else {
                  return { [FORM_ERROR]: error.toString() }
                }
              }
            }}
          >
            <div style={{ marginBottom: '20px' }}>
              <LabeledTextField name="email" size="lg" clearable bordered fullWidth color="primary" placeholder="Email"/>
            </div>
            <LabeledTextField name="password" placeholder="Password" size="lg" clearable bordered fullWidth color="primary" type="password"/>
            <Spacer y={1}/>
            <Button shadow color="primary" auto style={{ width: '100%' }} type="submit">
              Sign up
            </Button>
          </Form>
          <Spacer y={1}/>
          <h6 style={{ width: '100%', textAlign: 'center', borderBottom: '1px solid ' + props.theme.colors.border.value, lineHeight: '0.1em', fontWeight: 'normal', margin: '10px 0 20px' }}>
            <span style={{ background: props.theme.colors.backgroundContrast.value, padding: '0 10px' }}>
              or
            </span>
          </h6>
          <Spacer y={0.5}/>
          <Button shadow color="secondary" auto onClick={() => router.push('/login')}>
            Sign in
          </Button>
        </Card>
      </Container>
    </div>
  );
};

const SignUpPage: BlitzPage = (props: any) => {
  const currentUser = useCurrentUser();
  const router = useRouter();

  if (currentUser) router.push('/');

  return <SignUp {...props} />;
}

export default SignUpPage;

import { Button, Form, Input } from 'antd';
import React, { useEffect } from 'react';
import styled from 'styled-components';
import { toast } from 'react-toastify';
import { useNavigate } from 'react-router-dom';
import logo from './assets/logo.svg';

const Center = styled.div`
position: absolute;
left: 50%;
top: 50%;
transform: translate(-50%, -50%);
`;

const Login: React.FC = () => {
  const navigate = useNavigate();

  useEffect(() => {
    if (localStorage.getItem('access'))
      navigate('/dashboard');
  }, []);

  const onFinish = async (values: any) => {
    if (values.password !== values.repeatPassword) {
      toast('Passwords do not match');
      return;
    }
    let response;
    try {
      response = await fetch(
        process.env.REACT_APP_API_URL + '/v1/register', {
          method: 'POST',
          headers: { 'Content-Type': 'application/json' },
          body: JSON.stringify({ email: values.email, password: values.password }),
        },
      );
    } catch (_) {
      toast('Couldn\'t register');
    }
    if (response?.status === 400)
      toast((await response.json()).message);
    if (response?.status === 409)
      toast('Email is already registered');
    if (response?.status === 201) {
      toast('Signed up successfully!');
      navigate('/');
    }
  };

  const onFinishFailed = (errorInfo: any) => {
  };

  return (
    <Center>
      <img src={logo} style={{ marginBottom: '30px' }} />
      <Form
        name="basic"
        labelCol={{ span: 8 }}
        wrapperCol={{ span: 16 }}
        initialValues={{ remember: true }}
        onFinish={onFinish}
        onFinishFailed={onFinishFailed}
        autoComplete="off"
      >
        <Form.Item
          label="Email"
          name="email"
          rules={[{ required: true, message: 'Please input your email' }]}
        >
          <Input />
        </Form.Item>

        <hr style={{ marginBottom: '25px' }} />

        <Form.Item
          label="Password"
          name="password"
          rules={[{ required: true, message: 'Please input your password' }]}
        >
          <Input.Password />
        </Form.Item>

        <Form.Item
          label="Repeat"
          name="repeatPassword"
          rules={[{ required: true, message: 'Please input your password again' }]}
        >
          <Input.Password />
        </Form.Item>

        <Form.Item wrapperCol={{ offset: 8, span: 16 }}>
          <Button type="primary" htmlType="submit">
            Sign up
          </Button>
        </Form.Item>
      </Form>
    </Center>
  );
};

export default Login;

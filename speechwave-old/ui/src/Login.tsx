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

.ant-form-item-control {
  @media (max-width: 575px) {
    margin-left: 0px;
  }
}
`;

const Login: React.FC = () => {
  const navigate = useNavigate();

  useEffect(() => {
    if (localStorage.getItem('access'))
      navigate('/dashboard');
  }, []);

  const onFinish = async (values: any) => {
    let response;
    try {
      response = await (await fetch(
        process.env.REACT_APP_API_URL + '/v1/login', {
          method: 'POST',
          headers: { 'Content-Type': 'application/json' },
          body: JSON.stringify({ 'email': values['email'], 'password': values['password'] }),
        },
      )).json();
    } catch (_) {
      toast('Email or password is wrong');
    }
    if (!response.access)
      toast('Email or password is wrong');
    else {
      const date = new Date();
      date.setHours(date.getHours() + 12);
      localStorage.setItem('access', response.access);
      localStorage.setItem('expiry', date.toString());
      navigate('/dashboard');
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
          rules={[{ required: true, message: 'Please input your email!' }]}
        >
          <Input />
        </Form.Item>

        <Form.Item
          label="Password"
          name="password"
          rules={[{ required: true, message: 'Please input your password!' }]}
        >
          <Input.Password />
        </Form.Item>

        <Form.Item wrapperCol={{ offset: 8, span: 16 }}>
          <Button type="primary" htmlType="submit">
            Log in
          </Button>
          <Button type="link" style={{ marginLeft: '20px' }} onClick={() => navigate('/register')}>
            Register
          </Button>
        </Form.Item>
      </Form>
    </Center>
  );
};

export default Login;
